#include "scenes/MenuScene.h"
#include "SceneManager.h"
#include "scenes/ConfigScene.h"
#include "scenes/ScoreboardScene.h"
#include "GameStateManager.h"
#include "enums/GameState.h"
#include <iostream>

MenuScene::MenuScene() {}

MenuScene::~MenuScene() {
    cleanUp(); 
}

void MenuScene::init(SDL_Renderer *render) {
	renderer = render;
	TTF_CloseFont(font);
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 24);
    if (!font) {
        std::cerr << "Erro ao carregar a fonte: " << TTF_GetError() << std::endl;
    }
}

void MenuScene::handleInput(SDL_Event& event) {
	std::cout << "PRINTE" << std::endl;
	SceneManager& sceneManager = SceneManager::getInstance();
    if (event.type == SDL_QUIT) {

    } 
    else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
			std::cout << event.key.keysym.sym << std::endl;
            case SDLK_UP:
                selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                break;
            case SDLK_DOWN:
                selectedIndex = (selectedIndex + 1) % options.size();
                break;
            case SDLK_RETURN:
                if (options[selectedIndex] == "Iniciar Jogo") {
					sceneManager.changeScene(new Game());
                } else if (options[selectedIndex] == "Configuracoes") {
					sceneManager.changeScene(new ConfigScene());
                }else if (options[selectedIndex] == "Placar") {
					sceneManager.changeScene(new ScoreboardScene());
				}else if (options[selectedIndex] == "Sair") {
                    sceneManager.cleanUp();
					sceneManager.destroyWindow();
                }
                break;
            case SDLK_ESCAPE:
                break;
        }
    }
}

void MenuScene::update(float dt) {}

void MenuScene::renderText(const std::string& text, int x, int y, bool selected) {
	SceneManager& sceneManager = SceneManager::getInstance();
    SDL_Color color = selected ? SDL_Color{255, 255, 0, 255} : SDL_Color{255, 255, 255, 255};
	if (font) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(sceneManager.getRenderer(), surface);

        SDL_Rect renderQuad = {x, y, surface->w, surface->h};
        SDL_RenderCopy(sceneManager.getRenderer(), texture, nullptr, &renderQuad);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void MenuScene::render() {
	SceneManager& sceneManager = SceneManager::getInstance();
    int startY = sceneManager.getHeight() / 2 - (int)options.size() * 30;
    for (size_t i = 0; i < options.size(); ++i) {
        renderText(options[i], sceneManager.getWidth() / 4, startY + i * 40, i == selectedIndex);
    }

}

void MenuScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
