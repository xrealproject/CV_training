//============================================================================
// Name        : GettingStarted.cpp
// Author      : Jose Cisneros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/**
* How to Play AVI Files with OpenCV
*
* Author Nash
* License GPL
* Website http://nashruddin.com

#include <stdio.h>
#include "cv.h"
#include "highgui.h"


int main( int argc, char** argv )
{
IplImage *frame;
int key;

// supply the AVI file to play
//assert( argc == 2 );

// load the AVI file
CvCapture *capture = cvCaptureFromAVI( "sample2.mp4" );

// always check
if( !capture ) return 2;


// get fps, needed to set the delay
int fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );

// display video
cvNamedWindow( "video", 0 );

while( key != 'q' ) {
// get a frame
frame = cvQueryFrame( capture );

// always check
if( !frame ) break;

// display frame
cvShowImage( "video", frame );

// quit if user press 'q'
key = cvWaitKey( 1000 / fps );
}

// free memory
cvReleaseCapture( &capture );
cvDestroyWindow( "video" );

return 0;
}
*/


/**
*Display a Picture

#include "highgui.h"

int main( int argc, char** argv )
{
 IplImage* img = cvLoadImage( argv[1] );
 cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
 cvShowImage( "Example1", img );
 cvWaitKey(0);
 cvReleaseImage( &img );
 cvDestroyWindow( "Example1" );
}
*/

/**
* Play an AVI Video
*/
#include "highgui.h"

int main( int argc, char** argv ) {
 cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE );
 CvCapture* capture = cvCreateFileCapture( argv[1] );
 IplImage* frame;
 while(1) {
 frame = cvQueryFrame( capture );
 if( !frame ) break;
 cvShowImage( "Example2", frame );
 char c = cvWaitKey(33);
 if( c == 27 ) break;
 }
 cvReleaseCapture( &capture );
 cvDestroyWindow( "Example2" );
}
/**
*/

/**
* Play an AVI Video with an slide bar

#include "cv.h"
#include "highgui.h"
int g_slider_position = 0;
CvCapture* g_capture = NULL;
void onTrackbarSlide(int pos) {
 cvSetCaptureProperty(
 g_capture,
 CV_CAP_PROP_POS_FRAMES,
 pos
 );
}
int main( int argc, char** argv ) {
 cvNamedWindow( "Example3", CV_WINDOW_AUTOSIZE );
 g_capture = cvCreateFileCapture( argv[1] );
 int frames = (int) cvGetCaptureProperty(
 g_capture,
 CV_CAP_PROP_FRAME_COUNT
 );
 if( frames!= 0 ) {
 cvCreateTrackbar(
 "Position",
 "Example3",
 &g_slider_position,
 frames,
 onTrackbarSlide
 );
 }
 IplImage* frame;

 // While loop (as in Example 2) capture & show video
 while(1) {
  frame = cvQueryFrame( g_capture );
  if( !frame ) break;
  cvShowImage( "Example3", frame );
  char c = cvWaitKey(33);
  if( c == 27 ) break;
  }

  // Release memory and destroy window
 cvReleaseCapture( &g_capture );
 cvDestroyWindow( "Example3" );
 return(0);
}
*/
