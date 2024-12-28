#include "Graphics.h"

#include <iostream>

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;
uint32_t* Graphics::color_buffer = nullptr;
SDL_Texture* Graphics::color_buffer_texture = nullptr;
int Graphics::window_width = 800;
int Graphics::window_height = 600;

bool Graphics::initializeWindow(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0 ){
		std::cerr<<"Failed to initialize SDL Error: "<<SDL_GetError()<<std::endl;
		return false;
	}

	//create the window
	window = SDL_CreateWindow(
		"SDL Setup",
		SDL_WINDOWPOS_CENTERED,		
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS		
	);
	if(!window){
		std::cerr<<"SDL Error: "<<SDL_GetError()<<std::endl;
		return false;
	}
	std::cout << "SDL Window Created" << std::endl;

	//create renderer
	renderer = SDL_CreateRenderer(
        	window,
        	-1, // use default output/display device
        	0   // no special flags
    	);

	if (!renderer){
		std::cerr<<"SDL Error: "<<SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "SDL Renderer Created" << std::endl;
	
	return true;
}

void Graphics::initializeColorBuffer(){
	color_buffer = new uint32_t[window_width * window_height];

	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}


void Graphics::clearScreen(uint32_t color){
	for(int y=0; y<window_height;y++){
		for(int x=0; x< window_width; x++){
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void Graphics::renderColorBuffer(){
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int) (window_width * sizeof(uint32_t))		
	);

	SDL_RenderCopy(
		renderer,
		color_buffer_texture,
		NULL,
		NULL
	);

	SDL_RenderPresent(renderer);
}



void Graphics::drawPixel(int x, int y, uint32_t color){
	color_buffer[(window_width * y)+x] = color;
}

void Graphics::drawLine(int x1, int y1, int x2, int y2, uint32_t color){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1; // Step in x direction
    int sy = (y1 < y2) ? 1 : -1; // Step in y direction

    int err = dx - dy;

    while (true) {
        // Draw the current pixel
        drawPixel(x1, y1, color);

        // Check if the end point is reached
        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        // Adjust the error term and the next x or y
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Graphics::drawCircle(int h, int k, int r, uint32_t color) {
    int x = 0;
    int y = r;
    int d = 1 - r; // Decision parameter

    // Draw the initial points on the circle
    drawPixel(h + x, k + y, color);
    drawPixel(h - x, k + y, color);
    drawPixel(h + x, k - y, color);
    drawPixel(h - x, k - y, color);
    drawPixel(h + y, k + x, color);
    drawPixel(h - y, k + x, color);
    drawPixel(h + y, k - x, color);
    drawPixel(h - y, k - x, color);

    // Midpoint algorithm loop
    while (x < y) {
        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }

        // Draw the 8 symmetric points
        drawPixel(h + x, k + y, color);
        drawPixel(h - x, k + y, color);
        drawPixel(h + x, k - y, color);
        drawPixel(h - x, k - y, color);
        drawPixel(h + y, k + x, color);
        drawPixel(h - y, k + x, color);
        drawPixel(h + y, k - x, color);
        drawPixel(h - y, k - x, color);
    }
}

