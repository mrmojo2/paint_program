#include "DrawObject.h"
#include "Graphics.h"

#include <iostream>

PenCurve::PenCurve(std::vector<std::pair<int,int>> pixels):pixels(pixels){
}
void PenCurve::draw(){
	for(auto pixel:pixels){
		Graphics::drawPixel(pixel.first,pixel.second, 0xff000000);
	}
}
PenCurve::~PenCurve(){}




Line::Line(int x1, int y1, int x2, int y2): x1(x1),y1(y1),x2(x2),y2(y2){
}
void Line::draw(){
	Graphics::drawLine(x1,y1,x2,y2,0xff000000);
}
Line::~Line(){}




Circle::Circle(int h, int k, int r): h(h),k(k),r(r){}
void Circle::draw(){
	Graphics::drawCircle(h,k,r,0xff000000);	
}
Circle::~Circle(){}

