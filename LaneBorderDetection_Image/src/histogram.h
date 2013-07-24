//============================================================================
// Name        : Histograms.cpp
// Author      : Jose Cisneros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#if !defined HISTOGRAM
#define HISTOGRAM

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// cv::calcHist is a general function which can compute the histogram
// of multiple channels images of any pixel value type.
// Let's make it simpler to use by specializing a class for the case of 1-channel gray-level images:

class Histogram1D {
	private:
		int 		 histSize[1]; 	//number of bins
		float 		 hranges[2]; 	//min and max pixel value
		const float* ranges[1];
		int 		 channels[1]; 	// only one channel used here

	public:
		Histogram1D(){
			// Prepare arguments for 1D histogram
			histSize[0] = 256;
			hranges[0]  = 0.0;
			hranges[1]  = 255.0;
			ranges[0]   = hranges;
			channels[0] = 0;       // by default, we look at channel 0
		}

		// Sets the channel on which histogram will be calculated
		// by default it is channel 0
		void setChannel(int c) {
			channels[0] = c;
		}

		// Sets the range for the pixel values.
		// by default it is [0,255]
		void setRange(float minValue, float maxValue) {
			hranges[0] = minValue;
			hranges[1] = maxValue;
		}

		// Gets the max pixel value
		float getMinValue() {
			return hranges[0];
		}

		// Sets the number of bins in histogram
		// by default it is 256
		void setNBins(int nbins) {
			histSize[0] = nbins;
		}

		// Computes the 1D histogram
		cv::MatND getHistogram(const cv::Mat &image){
			cv::MatND hist;

			// Compute histogram
			cv::calcHist(&image,
					1,				// histogram from 1 image only
					channels,		// the channel used
					cv::Mat(),		// no mask is used
					hist,			// the resulting histogram
					1,				// it is a 1D histogram
					histSize,		// number of bins
					ranges			// pixel value range
			);
			return hist;
		}

		// Computes de 1D histogram and returns an image of it
		cv::Mat getHistogramImage(const cv::Mat &image)
		{
			// Compute histogram first
			cv::MatND hist = getHistogram(image);

			// Get min and max bin values
			double maxVal = 0;
			double minVal = 0;
			cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

			// Image on which to display histogram/
			cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));

			// Set highest point at 90% of nbins
			int hpt = static_cast<int>(0.9*histSize[0]);

			// Draw a vertical line for each bin
			for( int h = 0; h < histSize[0]; h++)
			{
				float binVal = hist.at<float>(h);
				int intensity = static_cast<int>(binVal*hpt/maxVal);

				// This function draws a line between 2 point
				cv::line(histImg, cv::Point(h,histSize[0]),
								  cv::Point(h,histSize[0]-intensity),
								  cv::Scalar::all(0));
			}
			return histImg;
		}


		// Computes de 1D histogram and returns an image of it
				cv::Mat getHistogramImageFromHist(const cv::MatND &hist)
				{

					// Get min and max bin values
					double maxVal = 0;
					double minVal = 0;
					cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

					// Image on which to display histogram/
					cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));

					// Set highest point at 90% of nbins
					int hpt = static_cast<int>(0.9*histSize[0]);

					// Draw a vertical line for each bin
					for( int h = 0; h < histSize[0]; h++)
					{
						float binVal = hist.at<float>(h);
						int intensity = static_cast<int>(binVal*hpt/maxVal);

						// This function draws a line between 2 point
						cv::line(histImg, cv::Point(h,histSize[0]),
										  cv::Point(h,histSize[0]-intensity),
										  cv::Scalar::all(0));
					}
					return histImg;
				}


		// Equalizes the source image
		cv::Mat equalize(const cv::Mat &image)
		{
			cv::Mat result;
			cv::equalizeHist(image,result);
			return result;
		}

		// Stretches the source image
		cv::Mat stretch(const cv::Mat &image, int minValue=0)
		{
			// Compute histogram first
			cv::Mat hist =getHistogram(image);

			// Find left extremity of the histogram
			int imin = 0;
			for( ; imin < histSize[0]; imin++)
			{
				std::cout << hist.at<float>(imin) << std::endl;
				if(hist.at<float>(imin) > minValue)
					break;
			}

			// Find right extremity of the image
			int imax = histSize[0]-1;
			for( ; imax >= 0; imax--)
			{
				if(hist.at<float>(imax) > minValue)
					break;
			}

			// Create lookup table
			int dims[1] = {256};
			cv::MatND lookup(1,dims,CV_8U);

			// Build lookup table
			for( int i = 0; i < 256; i++)
			{
				// Stretch between imin and imax
				if( i < imin ) lookup.at<uchar>(i) = 0;
				else if ( i > imax ) lookup.at<uchar>(i) = 255;
				// linear mapping
				else lookup.at<uchar>(i) = static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);
			}

			// Apply lookup table
			cv::Mat result;
			result = applyLookUp(image,lookup);

			return result;
		}

		// Applies a lookup table transforming an input image into a 1-channel image
		cv::Mat applyLookUp(const cv::Mat& image, const cv::MatND& lookup)
		{
			// Set output image (always 1-channel)
			cv::Mat result(image.rows,image.cols,CV_8U);
			cv::Mat_<uchar>::iterator itr  = result.begin<uchar>();

			// Iterates over the input image
			cv::Mat_<uchar>::const_iterator it    = image.begin<uchar>();
			cv::Mat_<uchar>::const_iterator itend = image.end<uchar>();

			// Applies lookup to each pixel
			for( ; it != itend; ++it, ++itr)
			{
				*itr = lookup.at<uchar>(*it);
			}

			return result;
		}
};

#endif
