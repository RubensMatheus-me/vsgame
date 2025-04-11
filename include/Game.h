#pragma once
#include <SDL2/SDL.h>
#include "Player.h"
#include "iostream"
#include <memory>
#include "Keyboard.h"

class Game {
	public:
		Game();
		~Game();

		void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

		void handleEvents();
		void update();
		void render();
		void clean();

		void loadResources();

		bool running() {return isRunning;}
		
		std::unique_ptr<Player> player;
		std::unique_ptr<Keyboard> keyboard;
		
	private:
        bool isRunning;
        int updateCounter = 0;
        SDL_Window *window;
        SDL_Renderer *renderer;

};