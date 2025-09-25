#include "scenes/ConfigScene.h"
#include "SceneManager.h"
#include "scenes/MenuScene.h"
#include <iostream>
#include <SDL.h>

ConfigScene::ConfigScene(Game* game) : game(game), font(nullptr) {}
ConfigScene::~ConfigScene() {
    cleanUp();
}

void ConfigScene::init(SDL_Renderer *render) {
	renderer = render;
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 24);
    if (!font) {
        std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
    }
}

void ConfigScene::handleInput(SDL_Event& event) {
    if (event.type == SDL_QUIT) {
    } 
    else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                break;
            case SDLK_DOWN:
                selectedIndex = (selectedIndex + 1) % options.size();
                break;
           case SDLK_RETURN:
                if (options[selectedIndex] == "Voltar ao Menu") {
                    SceneManager::getInstance().pushScene(new MenuScene(game));
                }
                break;
            case SDLK_ESCAPE:
                SceneManager::getInstance().changeScene(new MenuScene(game));
                break;
        }
    }
}

void ConfigScene::update(float dt) {}

void ConfigScene::renderText(const std::string& text, int x, int y, bool selected) {
    SDL_Color color = selected ? SDL_Color{255, 255, 0, 255} : SDL_Color{255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->getRenderer(), surface);

    SDL_Rect renderQuad = {x, y, surface->w, surface->h};
    SDL_RenderCopy(game->getRenderer(), texture, nullptr, &renderQuad);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void ConfigScene::render() {
    SDL_RenderClear(game->getRenderer());

    int startY = game->getHeight() / 2 - (int)options.size() * 30;
    for (size_t i = 0; i < options.size(); ++i) {
        renderText(options[i], game->getWidth() / 4, startY + i * 40, i == selectedIndex);
    }

    SDL_RenderPresent(game->getRenderer());
}

void ConfigScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
