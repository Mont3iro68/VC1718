
#include "Color.h"







void morph (Mat mask){
    
    Mat eroded = getStructuringElement( MORPH_RECT,Size(3,3));
    Mat dilated = getStructuringElement( MORPH_RECT,Size(8,8));
    erode(mask,mask,eroded);
    erode(mask,mask,eroded);
    dilate(mask,mask,dilated);

}

void findObject(Mat mask, Mat result, Scalar color ){
    vector<vector<Point> > contours;
    Mat temp;
    mask.copyTo(temp);
    findContours(mask, contours,RETR_CCOMP,CHAIN_APPROX_SIMPLE);
    for (unsigned int i = 0; i < contours.size();i++){
            double area = contourArea(contours[i]);
            if (area > 10000)
                drawContours(result,contours,-1,color,-1);
            }
}

bool option() {
	char *p, s[10];
        int n = 0;
        bool calibrate;

        while (n == 0){
        	printf("Enter 1-calibrate color or 2-test color detection:\n");
        	fgets(s,sizeof(s),stdin);
       		n = strtol(s, &p, 10);

        	switch(n) {
        		case 1:
        			calibrate = true;
        			break;
        		case 2:
        			calibrate = false;
        			break;
        		default:
        			printf("Wrong key\n");
        			n = 0;
        			break;
        	}
        }
        return calibrate;
}


int main(int, char**)
{
    
    bool calibrate = option();
        

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    

    cap.set(CAP_PROP_FRAME_WIDTH,640);
	cap.set(CAP_PROP_FRAME_HEIGHT,480);

	int max_slider = 255;

    Mat hsv, frame, mask, result,blurred, hsvBar;
    namedWindow("Trackbar");
    namedWindow("source", WINDOW_NORMAL);
    namedWindow("mask", WINDOW_NORMAL);
    namedWindow("Color Trackbar", WINDOW_NORMAL);
    namedWindow("result",WINDOW_NORMAL);
    
    createTrackbar("Low H", "Trackbar", 0, 179, NULL);
    createTrackbar("Low S", "Trackbar", 0, 255, NULL);
    createTrackbar("Low V", "Trackbar", 0, 255, NULL);
    createTrackbar("High H", "Trackbar", &max_slider, 179, NULL);
    createTrackbar("High S", "Trackbar", &max_slider, 255, NULL);
    createTrackbar("High V", "Trackbar", &max_slider, 255, NULL);

    createTrackbar("Red","Color Trackbar",0,255,NULL);
    createTrackbar("Green","Color Trackbar",0,255,NULL);
    createTrackbar("Blue","Color Trackbar",0,255,NULL);

    
    




    while(1){
        cap>>frame; // get a new frame from camera
        cap>>result;
        GaussianBlur(frame,blurred,Size(5,5),0,0);
        cvtColor(blurred,hsv,COLOR_BGR2HSV); 
        int objR = getTrackbarPos("Red","Color Trackbar");
        int objG = getTrackbarPos("Green","Color Trackbar");
        int objB = getTrackbarPos("Blue","Color Trackbar");
        



        if(calibrate){

        hsvBar =  imread("HSbar.png");



        int l_h = getTrackbarPos("Low H","Trackbar");
        int h_h = getTrackbarPos("High H","Trackbar");

        int l_s = getTrackbarPos("Low S","Trackbar");
        int l_v = getTrackbarPos("Low V","Trackbar");
        int h_s = getTrackbarPos("High S","Trackbar");
        int h_v = getTrackbarPos("High V","Trackbar");

        
        circle(hsvBar,Point(l_h * 4,255),5,Scalar(0,0,0),2,8,0); // low hue circle
        circle(hsvBar,Point(h_h * 4,255),5,Scalar(0,0,0),2,8,0); // high hue circle
        circle(hsvBar,Point(0,l_s),5,Scalar(0,0,0),2,8,0); //low saturation circle
        circle(hsvBar,Point(0,h_s),5,Scalar(0,0,0),2,8,0); //high saturation circle


        inRange(hsv,Scalar(l_h, l_s, l_v),Scalar(h_h,h_s,h_v),mask);
        morph(mask);
        findObject(mask,result,Scalar(objB,objG,objR));
        imshow("mask",mask);
        imshow("Trackbar", hsvBar);
        
        }else{
            Color yellow("yellow"), green("green"), blue("blue"), red("red");
           
            inRange(hsv,yellow.getHSVlow(),yellow.getHSVhigh(),mask);
            morph(mask);
            findObject(mask,result,Scalar(objB,objG,objR));
			
			inRange(hsv,green.getHSVlow(),green.getHSVhigh(),mask);
            morph(mask);
            findObject(mask,result,Scalar(objB,objG,objR));

            inRange(hsv,blue.getHSVlow(),blue.getHSVhigh(),mask);
            morph(mask);
            findObject(mask,result,Scalar(objB,objG,objR));            

            inRange(hsv,red.getHSVlow(),red.getHSVhigh(),mask);
            morph(mask);
            findObject(mask,result,Scalar(objB,objG,objR));
        }
        




        //imshow("source", frame);
        imshow("result",result);

        if(waitKey(30) >= 0) break;
    }
    cout << hsvBar.cols;
    destroyAllWindows();
    return 0;
}



