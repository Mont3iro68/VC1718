
#include "Color.h"

Color::Color(){
	setColor("Color");

}

Color::Color(string color){
	if(color == "blue"){
			setColor(color);
			//setHSVhigh();
			//setHSVlow();
	}
	if(color == "red"){
			setColor(color);
		
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
