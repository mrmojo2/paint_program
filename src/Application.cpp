#include "Application.h"
#include "Graphics.h"
#include "DrawObject.h"

#include <SDL2/SDL.h>
#include <iostream>

void Application::setup(){
	isRunning = Graphics::initializeWindow();
	Graphics::initializeColorBuffer();

}

void Application::input(){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
	
			if(event.key.keysym.sym == SDLK_p)
				currentTool = PEN;
			
			if(event.key.keysym.sym == SDLK_l)
				currentTool = LINE;
			
			if(event.key.keysym.sym == SDLK_c)
				currentTool = CIRCLE;
			break;
		case SDL_MOUSEMOTION:
			mousePos.first = event.motion.x;
			mousePos.second = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT){
				mouseDown = true;
				switch(currentTool){
					case PEN:
						currentObject = new PenCurve({mousePos});
						break;
					case LINE:
						currentObject = new Line(mousePos.first, mousePos.second, mousePos.first, mousePos.second);
						break;
					case CIRCLE:
						currentObject = new Circle(mousePos.first, mousePos.second, 0);
						break;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT){
				mouseDown = false;
				draw_objects.push_back(currentObject);
				currentObject = nullptr;	
			}
			break;
	}
}

void Application::update(){	
	if(mouseDown){
		switch(currentTool){
			case PEN:{
				PenCurve* pc = (PenCurve* )currentObject;

				std::cout << "mouse: " << mousePos.first << "," << mousePos.second << std::endl;
				
				pc->pixels.push_back(mousePos);
				break;
			}
			case LINE:{
				Line* l = (Line*)currentObject;
				l->x2 = mousePos.first;
				l->y2 = mousePos.second;
				std::cout << "lineEnd: " <<l->x2 << "," <<l->y2<< std::endl;
				break;
			}
			case CIRCLE:{
				Circle* c = (Circle* )currentObject;
		    		int dx = c->h - mousePos.first;		
		    		int dy = c->k - mousePos.second;
				int r = sqrt(dx*dx + dy*dy);
				c->r = r;		
			}

		}
	}
}

void Application::render(){
	Graphics::clearScreen(0xffffffff);		// clear screen in each "frame" 
	

	// draw all draw_objects!	
	for(auto object:draw_objects){
		object->draw();
	}
	
	//draw current object
	if(currentObject){
		currentObject->draw();
	}

		
	Graphics::renderColorBuffer();			//render to screen
}

Application::~Application(){

	//free sdl objects
	SDL_DestroyRenderer(Graphics::renderer);
	SDL_DestroyWindow(Graphics::window);
	SDL_DestroyTexture(Graphics::color_buffer_texture);
	delete [] Graphics::color_buffer;
	SDL_Quit();

	//free draw objects
	for(auto obj:draw_objects){
		delete obj;
	}
}
