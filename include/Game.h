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
#include "DamagePopupManager.h"
#include "Scene.h"

#include "Enemy.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "SpriteAnimation.h"
#include "LevelUpMenu.h"
#include "Timer.h"
#include "EnemySpawner.h"
#include "AudioManager.h"
#include "GameStateManager.h"
#include "WaveManager.h"
#include "DamagePopupManager.h"
#include "TextDisplayManager.h"


// const float MAX_FPS = 60.0f;

class Game : public Scene
{
	public:
		Game();
		~Game();

		bool isPaused = false;
		void setPaused(bool value) { isPaused = value; }
		bool getIsPaused() const { return isPaused; }

		void init(SDL_Renderer *renderer) override;

		void events();
		void update(float dt) override;
		void render() override;
		void cleanUp() override;

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
		void isDead();

		void handleInput(SDL_Event& event) override;

		void spawnEnemy();
		SDL_Renderer* getRenderer() const {return this->renderer;}
		
		std::unique_ptr<Player> player;
		std::unique_ptr<Keyboard> keyboard;
		std::unique_ptr<TileManager> tileManager;
		std::unique_ptr<CameraManager> camera;
		std::unique_ptr<DamagePopupManager> damagePopupManager;

		std::vector<std::unique_ptr<Enemy>> enemies;
		std::unique_ptr<CollisionManager> collision;
		std::unique_ptr<TickRate> tickRate;
		std::unique_ptr<SpriteAnimation> playerAnimation;
		std::unique_ptr<LevelUpMenu> levelUpMenu;
		std::vector<std::unique_ptr<SpriteAnimation>> ownedAnimations;
		std::unique_ptr<EnemySpawner> enemySpawner;
		std::unique_ptr<WaveManager> waveManager;
		std::unique_ptr<TextDisplayManager> textDisplay;
			
	private:
		static int width;
		static int height;
        bool isRunning;
		static bool debugMode;
        SDL_Window *window;
		Timer timerEvents;
		Timer gameTime;
};