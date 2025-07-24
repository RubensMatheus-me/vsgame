#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Player.h"
#include "Enemy.h"
#include "iostream"
#include <memory>
#include "Keyboard.h"
#include "Projectile.h"
#include "TickRate.h"
#include "Timer.h"
#include "TileManager.h"
#include "CameraManager.h"

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
		void updateXp();

		bool getIsRunning() const {return this->isRunning;}
		static int getWidth() {return width;}
		static int getHeight() {return height;}
		static bool getDebugMode() {return debugMode;}
		
		void setWidth(const int newWidth) {this->width = newWidth;}
		void setHeight(const int newHeight) {this->height = newHeight;}
		void setIsRunning(const bool newIsRunning) {this->isRunning = newIsRunning;}
		static void setDebugMode(const bool newDebugMode) {debugMode = newDebugMode;}
		void shootProjectile();
		void removeDeadEntities();

		
		void spawnEnemy();
		
		std::unique_ptr<Player> player;
		std::unique_ptr<Enemy> enemy;
		std::unique_ptr<Keyboard> keyboard;
		std::unique_ptr<TileManager> tileManager;
		std::unique_ptr<CameraManager> camera;
		
	private:
		static int width;
		static int height;
        bool isRunning;
		static bool debugMode;
        SDL_Window *window;
        SDL_Renderer *renderer;
		Timer timerEvents;
		Timer gameTime;
};