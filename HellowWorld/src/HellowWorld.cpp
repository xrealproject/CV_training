//============================================================================
// Name        : HellowWorld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <opencv/cv.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

//#include "opencv/cv.hpp"

/**
 * @file Drawing_1.cpp
 * @brief Simple sample code
 */


using namespace cv;

int main( int argc, char** argv )
{
  Mat image = imread( argv[1], 1 );

  if( argc != 2 || !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }
  namedWindow("daa",1);
  namedWindow( "Display Image", WINDOW_AUTOSIZE );
  imshow( "Display Image", image );

  waitKey(0);

  return 0;
}


