#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "DrawObject.h"

class Application{
public:
	bool isRunning;
	bool mouseDown = false;
	std::pair<int,int> mousePos;
	std::vector<DrawObject* > draw_objects;
	Tool currentTool = PEN;
	DrawObject* currentObject = nullptr;

	void setup();
	void input();
	void update();
	void render();

	Application()=default;
	~Application();
};


#endif
