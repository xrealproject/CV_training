//============================================================================
VideoFrameProcessor.cpp// Name        : VideoFrameProcessor.cpp
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

class VideoProcessor {
private:
	// the OpenCV video capture object
	VideoCapture capture;
	// the callback function to be called
	// for the processing of each frame
	void (*process)(Mat&, Mat&);
	// a bool to determine if the
	// process callback will be called
	bool callIt;
	// Input display window name
	string windowNameInput;
	// Output display window name
	string windowNameOutput;
	// delay between each frame processing
	int delay;
	// number of processed frames
	long fnumber;
	// stop at this frame number
	long frameToStop;
	// to stop the processing
	bool stop;


	// to et the next frame
	// could be: videofile or camera
	bool readNextFrame(Mat& frame) {
		return capture.read(frame);
	}

public:
	VideoProcessor() : callIt(true), delay(0), fnumber(0), frameToStop(-1), stop(false)  {}

	// Set the callback function that
	// will be called for each frame
	void setFrameProcessor(
			void(*frameProcessingCallback)
				(Mat&, Mat&)) {
		process = frameProcessingCallback;
	}

	// Set the name of the video file
	bool setInput(string filename) {
		fnumber = 0;
		// In case a resource was already
		// associated with the VideoCapture instance
		capture.release();
		//images.clear();
		// Open the video file
		return capture.open(filename);
	}

	// to display the processed frames
	void displayInput(string wn) {
		windowNameInput = wn;
		namedWindow(windowNameInput);
	}

	// to display the processed frames
	void displayOutput(string wn) {
		windowNameOutput = wn;
		namedWindow(windowNameOutput);
	}

	// do not display the processed frames
	void dontDisplay() {
		destroyWindow(windowNameInput);
		destroyWindow(windowNameOutput);
		windowNameInput.clear();
		windowNameOutput.clear();
	}

	// to grab (and process) the frames of the sequence
	void run() {
		//current frame
		Mat frame;
		// output frame
		Mat output;

		//if no capture device has been set
		if (!isOpened())
			return;
		stop = false;
		while (!isStopped()) {

			// read next frame if any
			if (!readNextFrame(frame))
				break;

			// display input frame
			if (windowNameInput.length() != 0)
				imshow(windowNameInput, frame);

			// calling the process function
			if (callIt) {
				// process the frame
				process(frame, output);
				//increment frame number
				fnumber++;
			} else {
				output = frame;
			}

			// display output frame
			if (windowNameOutput.length() != 0)
				imshow(windowNameOutput, output);

			// introduce a delay
			if (delay >= 0 && waitKey(delay) >= 0)
				stopIt();

			// check if we should stop
			if (frameToStop>=0 && getFrameNumber()==frameToStop)
				stopIt();
		}
	}

	// Stop the processing
	void stopIt() {
		stop = true;
	}

	// Is the process stopped?
	bool isStopped() {
		return stop;
	}

	// Is a capture device opened?
	bool isOpened() {
		return capture.isOpened();
	}

	// set a delay between each frame
	// 0 means wait at each frame
	// negative means no delay
	void setDelay(int d) {
		delay = d;
	}

	// One might also wish to simply open and play the video file.
	// We therefore have two methods to specify whether or not we want the callback function to be called.
	// process callback to be called
	void callProcess() {
		callIt = true;
	}

	// do not call process callback
	void donCallProcess() {
		callIt = false;
	}

	//The class also offers the possibility to stop at a certain frame number.
	void stopAtFrameNo(long frame) {
		frameToStop = frame;
	}

	// return the frame number if the next frame
	long getFrameNumber() {
		// get info of from the capture device
		long fnumber = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
		return fnumber;
	}

	// return the frame rate
	double getFrameRate() {
		// undefined for vector of images
		//if (images.size()!=0)
		//	return 0;
		double r = capture.get(CV_CAP_PROP_FPS);
		return r;
	}
};










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

	/* Using RGB2Lab conversion
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



void detectColor(Mat& image, Mat& imageColorDetected) {
	// 1. Crate image processor object
	ColorDetector cdetect;

	// 2. Read input image
	//Mat image = imread(argv[1]);
	//Mat imageColorDetected;
	//if (!image.data)
	//   return 0;

	// 3. Set the input parameters
	cdetect.setTargetColor(169,169,169); //here blue sky
	cdetect.setColorDistanceThreshold(50);

	//namedWindow("result");

	// 4. Process the image and display the result
	imageColorDetected = cdetect.process(image);
	//imshow("result",imageColorDetected);

	//namedWindow("image");
	//imshow("image",image);

	//waitKey();

	///////////////////////////////////////////////////////
	/*

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
			*/
}









void canny(Mat& img, Mat& out) {

	// Convert to gray
	if (img.channels()==3)
		cvtColor(img, out, CV_BGR2GRAY);

	// Compute Canny edges
	Canny(out, out, 100, 200);

	// Invert the image
	threshold(out, out, 128, 255, THRESH_BINARY_INV);
}



int main() {

	/*
	// Create instance
	VideoProcessor processor;
	// Open video file
	processor.setInput("test.avi");
	// Declare a window to display the video
	processor.displayInput("Input Video");
	processor.displayOutput("Output Video");
	// Play the video at the original frame rate
	processor.setDelay(1000./processor.getFrameRate());
	// Set the frame processor callback function
	processor.setFrameProcessor(canny);
	// Start the process
	processor.run();
	waitKey();
	*/



	// Create instance
	VideoProcessor processor;
	ColorDetector cdetect;



	// Open video file
	processor.setInput("sample3.mp4");
	// Declare a window to display the video
	processor.displayInput("Input Video");
	processor.displayOutput("Output Video");
	// Play the video at the original frame rate
	processor.setDelay(1000./processor.getFrameRate());
	// Set the frame processor callback function
	processor.setFrameProcessor(canny);
	// Start the process
	processor.run();
	waitKey();


}
