#pragma once
#include "Scene.h"
#include "Game.h"
#include <vector>
#include <string>

class PlacarScene : public Scene {
public:
    PlacarScene();
    ~PlacarScene() override;

    void init(SDL_Renderer *renderer) override;
    void handleInput(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void cleanUp() override;

private:
    Game* game;
    TTF_Font* font = nullptr;
    int selectedIndex = 0;
    std::vector<std::string> options = {
        "Voltar ao Menu"
    };

    void renderText(const std::string& text, int x, int y, bool selected);
};
