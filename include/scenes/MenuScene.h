#pragma once
#include "Scene.h"
#include "Game.h"

class MenuScene : public Scene {
	public:
		MenuScene(Game* game);
		~MenuScene();

		void init() override;
		void handleInput(SDL_Event& event) override;
		void update(float dt) override;
		void render() override;
		void cleanUp() override;

	private:
		void renderText(const std::string& text, int x, int y);
		Game* game;
		TTF_Font* font = nullptr;
};