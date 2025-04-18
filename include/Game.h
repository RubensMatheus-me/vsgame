#pragma once
#include <SDL2/SDL.h>
#include "Player.h"
#include "Enemy.h"
#include "iostream"
#include <memory>
#include "Keyboard.h"
#include "TickRate.h"
#include "Timer.h"

//const float MAX_FPS = 60.0f;

class Game {
	public:
		Game();
		~Game();

		void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

		void events();
		void update();
		void render();
		void clean();

		void loadResources();
		void limitFPS(float targetFPS);

		void initializeEntities();
		void updateFpsDisplay();
		void updateClockDisplay();

		bool getIsRunning() const {return this->isRunning;}
		int getWidth() const {return this->width;}
		int getHeight() const {return this->height;}
		
		void setWidth(const int newWidth) {this->width = newWidth;}
		void setHeight(const int newHeight) {this->height = newHeight;}
		void setIsRunning(const bool newIsRunning) {this->isRunning = newIsRunning;}
		
		std::unique_ptr<Player> player;
		std::unique_ptr<Enemy> enemy;
		std::unique_ptr<Keyboard> keyboard;
		
	private:
		int width;
		int height;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;

		Timer timer;
};