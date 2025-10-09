#pragma once

#include "Scene.h"
#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>

class ScoreboardScene : public Scene {
public:
    ScoreboardScene();
    ~ScoreboardScene();

    void init(SDL_Renderer* renderer) override;
    void handleInput(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void cleanUp() override;

private:
    void loadScores();
    void renderText(const std::string& text, int x, int y, SDL_Color color);

    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    std::vector<std::string> scores;
};
