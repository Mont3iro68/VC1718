
#include "Color.h"

Color::Color(){
	setColor("Color");

}

Color::Color(string color){
	if (color == "green"){
			setColor(color);
			setHSVlow(Scalar(45,90,50));
			setHSVhigh(Scalar(100,255,255));
	}
	if(color == "blue"){
			setColor(color);
			setHSVlow(Scalar(90,120,120));
			setHSVhigh(Scalar(130,255,255));
	}
	if(color == "red"){
			setColor(color);
			setHSVlow(Scalar(0,160,0));
			setHSVhigh(Scalar(179,255,255));
	}
	if(color == "yellow"){	
			setColor(color);
			setHSVlow(Scalar(15,130,50));
			setHSVhigh(Scalar(35,255,255));
	}
}

Color::~Color()
{
}

string Color::getColor(){
	return Color::color;
}

void Color::setColor(string c){
	Color::color = c;
}

Scalar Color::getHSVhigh(){
	return Color::HSVhigh;
}

void Color::setHSVhigh(Scalar high){
	Color::HSVhigh = high; 
}

Scalar Color::getHSVlow(){
	return Color::HSVlow;
}

void Color::setHSVlow(Scalar low){
	Color::HSVlow = low; 
}
