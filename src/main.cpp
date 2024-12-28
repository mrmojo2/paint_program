#include <iostream>

#include "Application.h"

int main(){
	std::cout << "hello world" <<std::endl;
	
	Application app;

	app.setup();
	while(app.isRunning){
		app.input();
		app.update();
		app.render();	
	}

	return 0;
}
