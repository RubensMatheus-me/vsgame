#pragma once
#include "Scene.h"
#include "Game.h"
#include <vector>
#include <string>

class MenuScene : public Scene {
public:
    MenuScene();
    ~MenuScene();

    void init(SDL_Renderer *renderer) override;
    void handleInput(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void cleanUp() override;
private:
    void renderText(const std::string& text, int x, int y, bool selected);

    Game* game;
    std::vector<std::string> options = {"Iniciar Jogo", "Configuracoes", "Placar","Sair"};
    int selectedIndex = 0;
    TTF_Font* font = nullptr;
	SDL_Texture* backgroundTexture = nullptr;
};
