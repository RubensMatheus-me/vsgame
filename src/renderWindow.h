#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class RenderWindow {
	public:
		RenderWindow(const char* title, int width, int height);
		SDL_Renderer* GetRenderer();
		void close();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

};
RenderWindow::RenderWindow(const char* title, int width, int height) : window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if(window == NULL) {
		std::cout << "not create window" << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(renderer == NULL) {
		std::cout << "not create renderer" << std::endl;
	}


}

SDL_Renderer* RenderWindow::GetRenderer()
{
	return renderer;
}

void RenderWindow::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	SDL_Quit();
}
