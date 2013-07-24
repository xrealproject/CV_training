
#include "colordetector.h"
        
cv::Mat ColorDetector::process(const cv::Mat &image) {
        
	// re-allocate binary map if necessary
	// same size as input image, but 1-channel
	result.create(image.rows,image.cols,CV_8U);

	// re-allocate intermediate image if necessary
	converted.create(image.rows,image.cols,image.type());
	// Converting to Lab color space
	//cv::cvtColor(image, converted, CV_BGR2Lab);
	converted = image.clone();

	// get the iterators
	cv::Mat_<cv::Vec3b>::const_iterator it= converted.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend= converted.end<cv::Vec3b>();
	cv::Mat_<uchar>::iterator itout= result.begin<uchar>();

	// for each pixel
	for ( ; it!= itend; ++it, ++itout) {

		/*
		// process each pixel ---------------------

		// compute distance from target color
		if (getDistance(*it)<minDist) {
			*itout= 255;

		} else {

			*itout= 0;
		}

		// end of pixel processing ----------------
		*/

		if (getDistance(*it) == 0)
			*itout= 0;
		//if (getDistance(*it) == 1)
		//	*itout = 0;
		//if (getDistance(*it) == 2)
			//*itout = 0;
		if (getDistance(*it) == 1)
			*itout = 255;
	}

	return result;
}

cv::Mat ColorDetector::overlapImage(const cv::Mat &image) {

	overlapped.create(image.rows,image.cols,image.type());

	image.copyTo(overlapped,result);

	return overlapped;
}
