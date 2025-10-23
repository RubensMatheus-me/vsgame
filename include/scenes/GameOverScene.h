#pragma once

#include "Scene.h"
#include <string>
#include <vector>
#include <SDL_ttf.h>

class GameOverScene : public Scene {
public:
    GameOverScene(const std::string& timeSurvived, int level, int enemiesKilled);
    ~GameOverScene();

    void init(SDL_Renderer *renderer) override;
    void handleInput(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void cleanUp() override;

private:
    void saveScore();
    void renderText(const std::string& text, int x, int y, SDL_Color color);

    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    std::string nameInput;
    std::string timeSurvived;
	int level;
	int enemiesKilled;

    bool saved = false;
};
