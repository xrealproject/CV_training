//============================================================================
// Name        : colorDetection.cpp
// Author      : Jose Cisneros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

#include "colordetector.h"

using namespace cv;
using namespace std;


class ColorDetectController {
private:
	//pointer to the singleton
	static ColorDetectController *singleton;

	// the algorithm class
	ColorDetector *cdetect;

	Mat image;  // The image to be processed
	Mat result; // The image result
	Mat overlapped; // The overlapped image

public:
	// private constructor
	ColorDetectController() {
		// setting up the application
		cdetect = new ColorDetector();
	}

	//In addition, you can also make the copy constructor and the operator= private to make sure
	//no one can create a copy of the Singleton's unique instance. The Singleton object is created
	//on demand, when a user of the class asks for an instance of this class. This is done using a
	//static method which creates the instance if it does not exist yet and then returns a pointer to
	//this instance:

	// Gets access to Singleton instance
	static ColorDetectController *getInstance() {
		// Create the instance at first call
		if (singleton == 0)
			singleton = new ColorDetectController;
		return singleton;
	}

	//Note that this implementation of the Singleton is not thread-safe however. Therefore, it should
	//not be used when concurrent threads need to access the Singleton instance.
	//Finally, since the Singleton instance has been created dynamically, the user must delete it
	//when it is not required anymore. Again, this is done through a static method:

	// Releases the singleton instance of this controller
	static void destroy() {
		if (singleton != 0) {
			delete singleton;
			singleton = 0;
		}
	}

	// Defining all the setters and getters that a user
	// would need to control the application

	// Sets the color distance threshold
	void setColorDistanceThreshold(int distance) {
		cdetect->setColorDistanceThreshold(distance);
	}

	// Gets the color distance threshold
	int getColorDistanceThreshold() const {
		return cdetect->getColorDistanceThreshold();
	}

	//Sets the color to be detected
	void setTargetColor(unsigned char red,
						unsigned char green,
						unsigned char blue) {
		cdetect->setTargetColor(red,green,blue);
	}

	// Gets the color to be detected
	void getTargetColor(unsigned char &red,
						unsigned char &green,
						unsigned char &blue) const {
		Vec3b color = cdetect->getTargetColor();
		red   = color[2];
		green = color[1];
		blue  = color[0];
	}

	// Sets the input image. Reads it from file.
	bool setInputImage(std::string filename) {
		image = imread(filename);
		if (!image.data)
			return false;
		else
			return true;
	}

	// Returns the current input image.
	const Mat getInputImage() const {
		return image;
	}

	// Performs image processing.
	void process() {
		result = cdetect->process(image);
	}

	// Returns the image result from the latest processing.
	const Mat getLastResult() const {
		return result;
	}

	// Finally, it is important to clean up everything when the application terminates
	// (and the controller is released).
	// Deletes processor objects created by the controller
	~ColorDetectController() {
		delete cdetect;
	}

	// **********************************************************
	// Added by me
	// Display Input image
	void dispInputImage() {
		namedWindow("image");
		imshow("image",image);
	}

	// Display Output Image (Result)
	void dispOutputImage() {
		namedWindow("result");
		imshow("result",result);
	}

	void overlap() {
		overlapped = cdetect->overlapImage(image);
	}

	const Mat getOverlappedImage() const {
		return overlapped;
	}

	void dispOverlappedImage() {
		namedWindow("overlapped");
		imshow("overlapped",overlapped);
	}

	// Returns the overlapped image from the latest processing.
	const Mat getLastOverlapped() const {
		return overlapped;
	}
};
