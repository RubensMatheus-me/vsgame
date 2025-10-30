#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>

class CreditsScene : public Scene {
public:
    CreditsScene();
    ~CreditsScene() override;

    void init(SDL_Renderer *renderer) override;
    void handleInput(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void cleanUp() override;

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
    TTF_Font* font = nullptr;
    int selectedIndex = 0;
    std::vector<std::string> options = {
    "Creditos:",
    "",
    "Rubens Matheus (IFPR)",
    "Daniel Leite (IFPR)",
    "Joao Marcos (IFPR)",
    "",
    "Agradecimentos ao professor:",
    "Eduardo Cruz (IFPR)",
    "",
    "Voltar ao Menu"
};


    void renderText(const std::string& text, int y, bool selected);
};
