#pragma once
#include "RenderWindow.h"
#include <iostream>
#include <SDL2/SDL.h>

int WIDTH = 1024;
int HEIGHT = 768;

int main(int argc, char* args[]) {
	bool gameRunning = true;

	RenderWindow window("game", WIDTH, HEIGHT);
	SDL_Renderer* renderer = window.GetRenderer();

	if(renderer == NULL) {
		std::cout << "renderer could be created" << std::endl;
	}

	SDL_Rect rect = {WIDTH / 2 - 50, HEIGHT / 2 - 50, 100, 100};
	int rectSpeed = 5;

	SDL_Event event;

	while(gameRunning) {
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				gameRunning = false;
			}
		}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		if(currentKeyStates[SDL_SCANCODE_UP]) {
            rect.y -= rectSpeed;
        }
        if(currentKeyStates[SDL_SCANCODE_DOWN]) {
            rect.y += rectSpeed; 
        }
        if(currentKeyStates[SDL_SCANCODE_LEFT]) {
            rect.x -= rectSpeed; 
        }
        if(currentKeyStates[SDL_SCANCODE_RIGHT]) {
            rect.x += rectSpeed; 
        }

		SDL_SetRenderDrawColor(renderer, 169, 169, 169, 1);

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}
	window.close();

	return 0;
}