#if !defined COLORDETECT
#define COLORDETECT

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;

class ColorDetector {

  private:

          // minimum acceptable distance
          int minDist; 

          // target color
          cv::Vec3b target; 

          // image containing resulting binary map
          cv::Mat result;

          // image containing color converted image
          cv::Mat converted;

          // overlapped image
          cv::Mat overlapped;

          // inline private member function
          // Computes the distance from target color.
          int getDistance(const cv::Vec3b& color) const {
                 // return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0]-target[0],color[1]-target[1],color[2]-target[2])));
        	  //return abs(color[0]-target[0])+
        			  //abs(color[1]-target[1])+
        			  //abs(color[2]-target[2]);
        	 if (color[0]>185 || color[0]<25) // || color[2]<65 )//|| color[1]<20 || color[1]>230)  // Para grau_frame.jpg
        	 //if (color[1]<25 || color[1]>80)
        	 //if (color[2]>150)
        		 return 0;
        	 //if (color[1]>150)
        		  //return 0;
        	 return 1;
          }

  public:

          // empty constructor
          ColorDetector() : minDist(50) {

        	  // default parameter initialization here
        	  target[0]= target[1]= target[2]= 0;
          }

          // Getters and setters

          // Sets the color distance threshold.
          // Threshold must be positive, otherwise distance threshold
          // is set to 0.
          void setColorDistanceThreshold(int distance) {

        	  if (distance<0)
        		  distance=0;
        	  minDist= distance;
          }

          // Gets the color distance threshold
          int getColorDistanceThreshold() const {

        	  return minDist;
          }

          // Sets the color to be detected
          void setTargetColor(unsigned char red, unsigned char green, unsigned char blue) {

        	  // Temporary 1-pixel image
        	  cv::Mat tmp(1,1,CV_8UC3);
        	  tmp.at<cv::Vec3b>(0,0)[0]= blue;
        	  tmp.at<cv::Vec3b>(0,0)[1]= green;
        	  tmp.at<cv::Vec3b>(0,0)[2]= red;

              // Converting the target to Lab color space 
              cvtColor(tmp, tmp, CV_BGR2Lab);

          target= tmp.at<cv::Vec3b>(0,0);
          }

          // Sets the color to be detected
          void setTargetColor(cv::Vec3b color) {

        	  cv::Mat tmp(1,1,CV_8UC3);
        	  tmp.at<cv::Vec3b>(0,0)= color;

              // Converting the target to Lab color space 
              cvtColor(tmp, tmp, CV_BGR2Lab);

              target= tmp.at<cv::Vec3b>(0,0);
          }

          // Gets the color to be detected
          cv::Vec3b getTargetColor() const {

        	  return target;
          }

          // Processes the image. Returns a 1-channel binary image.
          cv::Mat process(const cv::Mat &image);

          cv::Mat overlapImage(const cv::Mat &image);
};


#endif
