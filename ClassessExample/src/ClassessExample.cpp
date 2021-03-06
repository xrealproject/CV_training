//============================================================================
// Name        : ClassessExample.cpp
// Author      : Jose Cisneros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////////////////////////////////////
// Defining Class attributes ////////////////////
/////////////////////////////////////////////////

class ColorDetector {
private:
	// minimum acceptable distance
	int minDist;
	// target color
	Vec3b target;
	// image containing resulting binary map
	Mat result;
	// image containing color converted image
	cv::Mat converted;

	//in-line private member function
	//Computes the distance from target color
	int getDistance(const Vec3b& color) const {
		return abs(color[0] - target[0]) +
			   abs(color[1] - target[1]) +
			   abs(color[2] - target[2]);
	}

public:
	// Defining constructor, that initialize all input parameters
	// to their default values.
	//empty constructor
	ColorDetector() : minDist(100)
	{
		//default parameter initialization here
		target[0] = target[1] = target[2] = 0;
	}

	// Providing the user with the appropriate getters and setters.

	// Sets the color distance threshold.
	// Threshold must be positive,
	// otherwise distance threshold is set to 0.
	void setColorDistanceThreshold(int distance) {
		if (distance<0)
			distance = 0;
		minDist = distance;
	}

	// Gets the color distance threshold
	int getColorDistanceThreshold() const {
		return minDist;
	}

	// Sets the color to be detected
	void setTargetColor(unsigned char red,
						unsigned char green,
						unsigned char blue) {

		// BGR order
		target[2] = red;
		target[1] = green;
		target[0] = blue;

		/* Using RGB2Lab conversion
		// Temporary 1-pixel image
		Mat tmp(1,1,CV_8UC3);
		tmp.at<Vec3b>(0,0)[0] = blue;
		tmp.at<Vec3b>(0,0)[1] = green;
		tmp.at<Vec3b>(0,0)[2] = red;

		// Converting the target to Lab color space
		cvtColor(tmp, tmp, CV_BGR2Lab);
		target = tmp.at<Vec3b>(0,0);
		*/
	}


	// Sets the color to be detected
	void setTargetColor(Vec3b color) {
		target = color;
	}

	// Gets the color to be detected
	Vec3b getTargetColor() const {
		return target;
	}

	// Processes the image. Returns a 1-channel binary image.
	Mat process(const Mat &image);
};


Mat ColorDetector::process(const Mat &image) {
	// re-allocate binary map if necessary
	// same size as input image, but 1-channel
	result.create(image.rows, image.cols, CV_8U);

	//////////////////////////////////////////////////
	// re-allocate intermediate image if necessary
	converted.create(image.rows, image.cols, image.type());

	// Converting to Lab color spaces
	cvtColor(image, converted, CV_BGR2Lab);
	//////////////////////////////////////////////////

	// get the iterators
	Mat_<Vec3b>::const_iterator it    = image.begin<Vec3b>();
	Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();

	/* Usind RGB2Lab conversion
		Mat_<Vec3b>::const_iterator it    = image.begin<Vec3b>();
		Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
	 */

	Mat_<uchar>::iterator       itout = result.begin<uchar>();

	// for each pixel
	for (; it != itend; ++it, ++itout) {
		// process each pixel -------------------------
		// compute distance from target color
		if (getDistance(*it) < minDist) {
			*itout = 255;
		} else {
			*itout = 0;
		}
		// end of pixel processing --------------------
	}
	return result;
}


int main( int argc, char** argv )
{
	// 1. Crate image processor object
	ColorDetector cdetect;

	// 2. Read input image
	Mat image = imread(argv[1]);
	Mat imageColorDetected;
	if (!image.data)
		return 0;

	// 3. Set the input parameters
	cdetect.setTargetColor(230,230,230); //here blue sky
	cdetect.setColorDistanceThreshold(150);

	namedWindow("result");

	// 4. Process the image and display the result
	imageColorDetected = cdetect.process(image);
	imshow("result",imageColorDetected);

	namedWindow("image");
	imshow("image",image);

	waitKey();

	///////////////////////////////////////////////////////

	Mat imagemodified = image.clone();

	const int nrows = imagemodified.rows;
	const int ncols = imagemodified.cols;
	for (int i=0; i<nrows; i++) {
				for (int j=0; j<ncols; j++) {
					if (imageColorDetected.at<uchar>(i,j) == 255) {
						//imagemodified.at<uchar>(j,i)=255;
					} else if (imageColorDetected.at<uchar>(i,j) == 0) {
						imagemodified.at<cv::Vec3b>(i,j)[0]=05;
						imagemodified.at<cv::Vec3b>(i,j)[1]=0;
						imagemodified.at<cv::Vec3b>(i,j)[2]=0;
					}

				}
			}
	waitKey();

	namedWindow("result2");
	imshow("result2",imagemodified);
	///////////////////////////////////////////////////////

	waitKey();
	return 0;
}

/*
class ColorDetector {

  private:

  public:
          // Sets the color to be detected
          void setTargetColor(unsigned char red, unsigned char green, unsigned char blue) {

                  cv::Mat tmp(1,1,CV_8UC3);
          tmp.at<cv::Vec3b>(0,0)[0]= blue;
          tmp.at<cv::Vec3b>(0,0)[1]= green;
          tmp.at<cv::Vec3b>(0,0)[2]= red;

              // Converting the target to Lab color space
              cv::cvtColor(tmp, tmp, CV_BGR2Lab);

          target= tmp.at<cv::Vec3b>(0,0);
          }

          // Sets the color to be detected
          void setTargetColor(cv::Vec3b color) {

                  cv::Mat tmp(1,1,CV_8UC3);
          tmp.at<cv::Vec3b>(0,0)= color;

              // Converting the target to Lab color space
              cv::cvtColor(tmp, tmp, CV_BGR2Lab);

          target= tmp.at<cv::Vec3b>(0,0);
          }


};
*/
