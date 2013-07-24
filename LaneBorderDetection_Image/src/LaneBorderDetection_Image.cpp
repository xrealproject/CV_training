//============================================================================
// Name        : LaneBorderDetection_Image.cpp
// Author      : Jose Cisneros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// colorDetection_SingletonController
#include "colordetector.h"
#include "colorDetectController.h"

// objectFinder_Backprojection
#include "histogram.h"	// 	Histogram
#include "colorhistogram.h"
#include "objectFinder_Backprojection.h"



int main( int argc, char** argv )
{
	cout << "Applying a lane border detection in an image" << endl; // prints Backprojecting a Histogram to Detect Specific Image Content

	if(argc != 2) return -1;

	cv::Mat image_in = cv::imread(argv[1]);


	// *******************************************************
	cout << image_in.size() << endl;
	cv::Vec3b intensity = image_in.at<cv::Vec3b>(300,640);
	cout << image_in.at<cv::Vec3b>(640,300)[0] << endl;
	cout << image_in.at<cv::Vec3b>(641,300)[1] << endl;
	cout << image_in.at<cv::Vec3b>(642,300)[2] << endl;
	float blue = intensity.val[0];
	float green = intensity.val[1];
	float red = intensity.val[2];
	cout << blue << endl;
	cout << green << endl;
	cout << red << endl;
	// *******************************************************



	// ******************* Blue Image
	cv::Mat blueImage;
	//blueImage.create(image_in.rows,image_in.cols,CV_8U);
	blueImage = image_in.clone();
	// get the iterators
	//cv::Mat_<cv::Vec3b>::const_iterator it= image_in.begin<cv::Vec3b>();
	//cv::Mat_<cv::Vec3b>::const_iterator itend= image_in.end<cv::Vec3b>();
	//cv::Mat_<uchar>::iterator itout= blueImage.begin<uchar>();

	// for each pixel
	for ( int row = 0; row!= image_in.rows; row++)
	{
		for ( int col = 0; col != image_in.cols; col++)
		{
			blueImage.at<Vec3b>(row,col)[1] = 0;
			blueImage.at<Vec3b>(row,col)[2] = 0;
		}

	}

	// Display the image of contours
	cv::namedWindow("Blue Image");
	cv::imshow("Blue Image",blueImage);

	// Histogram Object
	ColorHistogram h_b;

	// Compute the blue histogram
	cv::MatND histo_b = h_b.getBlueHistogram(blueImage);

	// Display a histogram as an image
	cv::namedWindow("Blue histogram");
	cv::imshow("Blue histogram",h_b.getHistogramImageFromHist(histo_b));
	cv::waitKey();



	// ******************* Green Image
	cv::Mat greenImage;
	//blueImage.create(image_in.rows,image_in.cols,CV_8U);
	greenImage = image_in.clone();
	// get the iterators
	//cv::Mat_<cv::Vec3b>::const_iterator it= image_in.begin<cv::Vec3b>();
	//cv::Mat_<cv::Vec3b>::const_iterator itend= image_in.end<cv::Vec3b>();
	//cv::Mat_<uchar>::iterator itout= greenImage.begin<uchar>();


	// for each pixel
	for ( int row = 0; row!= image_in.rows; row++)
	{
		for ( int col = 0; col != image_in.cols; col++)
		{

			greenImage.at<Vec3b>(row,col)[0] = 0;
			greenImage.at<Vec3b>(row,col)[2] = 0;

		}
	}

	// Display the image of contours
	cv::namedWindow("Green Image");
	cv::imshow("Green Image",greenImage);

	// Histogram Object
	ColorHistogram h_g;

	// Compute the green histogram
	cv::MatND histo_g = h_g.getGreenHistogram(greenImage);

	// Display a histogram as an image
	cv::namedWindow("Green histogram");
	cv::imshow("Green histogram",h_g.getHistogramImageFromHist(histo_g));
	cv::waitKey();



	// ******************* Red Image
	cv::Mat redImage;
	blueImage.create(image_in.rows,image_in.cols,CV_8U);
	redImage = image_in.clone();
	// get the iterators
	//cv::Mat_<cv::Vec3b>::const_iterator it= image_in.begin<cv::Vec3b>();
	//cv::Mat_<cv::Vec3b>::const_iterator itend= image_in.end<cv::Vec3b>();
	//cv::Mat_<uchar>::iterator itout= greenImage.begin<uchar>();

	// for each pixel
	for ( int row = 0; row!= image_in.rows; row++)
	{
		for ( int col = 0; col != image_in.cols; col++)
		{
			redImage.at<Vec3b>(row,col)[0] = 0;
			redImage.at<Vec3b>(row,col)[1] = 0;
		}
	}

	// Display the image of contours
	cv::namedWindow("Red Image");
	cv::imshow("Red Image",redImage);

	// Histogram Object
	ColorHistogram h_r;

	// Compute the red histogram
	cv::MatND histo_r = h_r.getRedHistogram(redImage);

	// Display a histogram as an image
	cv::namedWindow("Red histogram");
	cv::imshow("Red histogram",h_r.getHistogramImageFromHist(histo_r));
	cv::waitKey();



	//cv::Mat image = cv::imread(argv[1]);

	// 1. Set the input image
	ColorDetectController::getInstance()->setInputImage(argv[1]);

	// 2. Set the input paramaters
	ColorDetectController::getInstance()->setTargetColor(220,220,220);
	ColorDetectController::getInstance()->setColorDistanceThreshold(60);

	// 3. Process the image and display input image and result
	ColorDetectController::getInstance()->process();			// colordetector.cpp
	ColorDetectController::getInstance()->dispInputImage();
	ColorDetectController::getInstance()->dispOutputImage();

	waitKey();

	///////////////////////////////////////////////////////
	ColorDetectController::getInstance()->overlap();
	ColorDetectController::getInstance()->dispOverlappedImage();
	///////////////////////////////////////////////////////

	waitKey();

	// Apply Canny algorithm
	//cv::Mat image = ColorDetectController::getInstance()->getLastOverlapped();
	//cv::Mat image = cv::imread(argv[1]);
	cv::Mat contours;
	cv::Canny(image_in,contours,100,400);
	cv::Mat contoursInv;
	cv::threshold(contours,contoursInv,128,255,cv::THRESH_BINARY_INV);

	// Display the image of contours
	cv::namedWindow("Canny Contours");
	cv::imshow("Canny Contours",contoursInv);

	waitKey();

	//Mat ccontoursInv;
	//cvtColor(contoursInv, ccontoursInv, CV_GRAY2BGR);


	vector<Vec4i> lines;
	HoughLinesP(contours, lines, 1, CV_PI/180, 50, 120, 15 );   // Valores para grau2_frame.jpg
	//HoughLinesP(contours, lines, 1, CV_PI/180, 50, 80, 15 ); // Valores para pistaTaller_frame.jpg
	float dy;
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		cout << l << endl;
		if (l[2] == l[0])
			dy = 0.01;
		else
			dy = l[2] - l[0];

		if (abs((l[3]-l[1])/dy) > 0.2)
			line( image_in, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 2, CV_AA);
	}

	imshow("detected lines", image_in);

	waitKey();

	return 0;
}
