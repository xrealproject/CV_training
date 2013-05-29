//============================================================================
// Name        : ReadingVideoSequences.cpp
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


int main() {
	// Open the video file
	VideoCapture capture("test.avi");
	// check if video successfully opened
	if (!capture.isOpened())
		return 1;
	// Get the frame rate
	double rate = capture.get(CV_CAP_PROP_FPS);
	bool stop(false);
	Mat frame; // current video frame
	namedWindow("Extracted Frame");
	// Delay between each frame in ms
	// corresponds to video frame rate
	int delay = 1000/rate;
	// for all frames in video
	while (!stop) {
		// read next frame if any
		if (!capture.read(frame))
			break;
		imshow("Extracted Frame", frame);
		// introduce a delay
		// or press key to stop
		if (waitKey(delay)>=0)
			stop = true;
	}

	// Close the video file.
	// Not required since called by destructor
	capture.release();
}



/*
To open a video, you simply need to specify the video filename. This can be done by providing
the name of the file in the constructor of the cv::VideoCapture object. It is also possible to
use the open method if the cv::VideoCapture has already been created. Once the video
has successfully opened (this can be verified through the isOpened method), it is possible
to start frame extraction. It is also possible to query the cv::VideoCapture object for
information associated with the video file by using its get method with the appropriate flag. In
the preceding example, we obtained the frame rate using the CV_CAP_PROP_FPS flag. Since
it is a generic function, it always returns a double even if in some cases another type would be
expected. For example, the total number of frames in the video file would be obtained (as an
integer) as follows:
long t= static_cast<long>(
capture.get(CV_CAP_PROP_FRAME_COUNT));
Have a look at the different flags available in the OpenCV documentation in order to find out
what information can be obtained from the video.
There is also a set method that allows you to input some parameter to the
cv::VideoCapture instance. For example, you can request to move to a specific frame
using the CV_CAP_PROP_POS_FRAMES:
// goto frame 100
double position= 100.0;
capture.set(CV_CAP_PROP_POS_FRAMES, position);
You can also specify the position in milliseconds using CV_CAP_PROP_POS_MSEC, or
specify the relative position inside the video using CV_CAP_PROP_POS_AVI_RATIO (with
0.0 corresponding to the beginning of the video and 1.0 to the end). The method returns
true if the requested parameter setting is successful.
Once the video captured is successfully opened (this is verified by the isOpened method), the
frames can be sequentially obtained by repetitively calling the read method as we did in the
example of the previous section. One can equivalently call the overloaded reading operator:
capture >> frame;
It is also possible to call the two basic methods:
capture.grab();
capture.retrieve(frame);

 */


/* VideoCapture::get
Returns the specified VideoCapture property
C++: double VideoCapture::get(int propId

Property identifier. It can be one of the following:
	CV_CAP_PROP_POS_MSEC Current position of the video file in milliseconds or video capture timestamp.
	CV_CAP_PROP_POS_FRAMES 0-based index of the frame to be decoded/captured next.
	CV_CAP_PROP_POS_AVI_RATIO Relative position of the video file: 0 - start of the film, 1 - end of the film.
	CV_CAP_PROP_FRAME_WIDTH Width of the frames in the video stream.
	CV_CAP_PROP_FRAME_HEIGHT Height of the frames in the video stream.
	CV_CAP_PROP_FPS Frame rate.
	CV_CAP_PROP_FOURCC 4-character code of codec.
	CV_CAP_PROP_FRAME_COUNT Number of frames in the video file.
	CV_CAP_PROP_FORMAT Format of the Mat objects returned by retrieve() .
	CV_CAP_PROP_MODE Backend-specific value indicating the current capture mode.
	CV_CAP_PROP_BRIGHTNESS Brightness of the image (only for cameras).
	CV_CAP_PROP_CONTRAST Contrast of the image (only for cameras).
	CV_CAP_PROP_SATURATION Saturation of the image (only for cameras).
	CV_CAP_PROP_HUE Hue of the image (only for cameras).
	CV_CAP_PROP_GAIN Gain of the image (only for cameras).
	CV_CAP_PROP_EXPOSURE Exposure (only for cameras).
	CV_CAP_PROP_CONVERT_RGB Boolean flags indicating whether images should be converted to RGB.
	CV_CAP_PROP_WHITE_BALANCE Currently not supported
	CV_CAP_PROP_RECTIFICATION Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)

Note: When querying a property that is not supported by the backend used by the VideoCapture class, value 0 is returned.
*/


/*VideoCapture::set
C++: bool VideoCapture::set(int propId, double value)

Parameters:
propId –
Property identifier. It can be one of the following:
	CV_CAP_PROP_POS_MSEC Current position of the video file in milliseconds.
	CV_CAP_PROP_POS_FRAMES 0-based index of the frame to be decoded/captured next.
	CV_CAP_PROP_POS_AVI_RATIO Relative position of the video file: 0 - start of the film, 1 - end of the film.
	CV_CAP_PROP_FRAME_WIDTH Width of the frames in the video stream.
	CV_CAP_PROP_FRAME_HEIGHT Height of the frames in the video stream.
	CV_CAP_PROP_FPS Frame rate.
	CV_CAP_PROP_FOURCC 4-character code of codec.
	CV_CAP_PROP_FRAME_COUNT Number of frames in the video file.
	CV_CAP_PROP_FORMAT Format of the Mat objects returned by retrieve() .
	CV_CAP_PROP_MODE Backend-specific value indicating the current capture mode.
	CV_CAP_PROP_BRIGHTNESS Brightness of the image (only for cameras).
	CV_CAP_PROP_CONTRAST Contrast of the image (only for cameras).
	CV_CAP_PROP_SATURATION Saturation of the image (only for cameras).
	CV_CAP_PROP_HUE Hue of the image (only for cameras).
	CV_CAP_PROP_GAIN Gain of the image (only for cameras).
	CV_CAP_PROP_EXPOSURE Exposure (only for cameras).
	CV_CAP_PROP_CONVERT_RGB Boolean flags indicating whether images should be converted to RGB.
	CV_CAP_PROP_WHITE_BALANCE Currently unsupported
	CV_CAP_PROP_RECTIFICATION Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)
value – Value of the property.
 */
