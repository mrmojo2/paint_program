#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <vector>
#include <utility>


enum Tool{
	PEN,
	LINE,
	CIRCLE
};

class DrawObject{
public:
	//uint32_t color;
	virtual void draw() = 0;
	virtual ~DrawObject() = default;
};

class PenCurve:public DrawObject{
public:
	std::vector<std::pair<int,int>> pixels;

	PenCurve(std::vector<std::pair<int,int>> pixels);
	~PenCurve();
	void draw();
};

class Line:public DrawObject{
public:
	int x1,x2,y1,y2;
	
	Line(int x1, int x2, int y1, int y2);
	~Line();
	void draw();
};

class Circle:public DrawObject{
public:
	int h,k,r;

	Circle(int h, int k, int r);
	~Circle();
	void draw();
};

#endif
