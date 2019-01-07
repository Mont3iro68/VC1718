#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;



class Color
{
private:
	string color;
	Scalar HSVhigh, HSVlow;


public:
	Color();
	~Color();

	Color(string name);
	string getColor();
	void setColor(string color);
	Scalar getHSVhigh();
	void setHSVhigh(Scalar hsv);
	Scalar getHSVlow();
	void setHSVlow(Scalar hsv);

};