#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    

    cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	int max_slider = 255;
    Mat hsv, frame, mask, result,blurred;
    namedWindow("Trackbar");
    namedWindow("source", WINDOW_NORMAL);
    namedWindow("mask", WINDOW_NORMAL);
    namedWindow("Color Trackbar", WINDOW_NORMAL);
    
    createTrackbar("Low H", "Trackbar", 0, 179, NULL);
    createTrackbar("Low S", "Trackbar", 0, 254, NULL);
    createTrackbar("Low V", "Trackbar", 0, 254, NULL);
    createTrackbar("High H", "Trackbar", &max_slider, 179, NULL);
    createTrackbar("High S", "Trackbar", &max_slider, 254, NULL);
    createTrackbar("High V", "Trackbar", &max_slider, 254, NULL);

    createTrackbar("Red","Color Trackbar",0,254,NULL);
    createTrackbar("Green","Color Trackbar",0,254,NULL);
    createTrackbar("Blue","Color Trackbar",0,254,NULL);

    vector<vector<Point> > contours;

    while(1){
        cap>>frame; // get a new frame from camera
        
        GaussianBlur(frame,blurred,Size(5,5),0,0);
        cvtColor(blurred,hsv,COLOR_BGR2HSV); 

        int l_h = getTrackbarPos("Low H","Trackbar");
        int l_s = getTrackbarPos("Low S","Trackbar");
        int l_v = getTrackbarPos("Low V","Trackbar");
        int h_h = getTrackbarPos("High H","Trackbar");
        int h_s = getTrackbarPos("High S","Trackbar");
        int h_v = getTrackbarPos("High V","Trackbar");
        int objR = getTrackbarPos("Red","Color Trackbar");
        int objG = getTrackbarPos("Green","Color Trackbar");
        int objB = getTrackbarPos("Blue","Color Trackbar");



        inRange(hsv,Scalar(l_h, l_s, l_v),Scalar(h_h,h_s,h_v),mask);
        findContours( mask, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
      	
        for (unsigned int i = 0; i < contours.size();i++){
        	double area = contourArea(contours[i]);
        	if (area > 10000)
        		drawContours(frame,contours,-1,Scalar(objB,objG,objR),-1);
        	}


        imshow("source", frame);
        imshow("mask",mask);
        if(waitKey(30) >= 0) break;
    }
    destroyAllWindows();
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
