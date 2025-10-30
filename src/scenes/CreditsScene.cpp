#include "scenes/CreditsScene.h"
#include "SceneManager.h"
#include "scenes/MenuScene.h"
#include <iostream>
#include <SDL.h>

CreditsScene::CreditsScene() : font(nullptr), backgroundTexture(nullptr) {}
CreditsScene::~CreditsScene() {
    cleanUp();
}

void CreditsScene::init(SDL_Renderer *render) {
    renderer = render;
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 20);
    if (!font) {
        std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
    }
}

void CreditsScene::handleInput(SDL_Event& event) {
    SceneManager& sceneManager = SceneManager::getInstance();

    if (event.type == SDL_QUIT) {
        sceneManager.setIsRunning(false);
    } 
    else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                selectedIndex = (selectedIndex == 0) ? 1 : 0;
                break;

            case SDLK_RETURN:
                if (selectedIndex == 1) { 
                    sceneManager.changeScene(new MenuScene());
                }
                break;

            case SDLK_ESCAPE:
                sceneManager.changeScene(new MenuScene());
                break;
        }
    }
}

void CreditsScene::update(float dt) {}

void CreditsScene::renderText(const std::string& text, int y, bool selected) {
    SceneManager& sceneManager = SceneManager::getInstance();
    if (!font || !renderer) return;

    SDL_Color color = selected ? SDL_Color{255, 255, 0, 255} : SDL_Color{255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int textX = (sceneManager.getWidth() - surface->w) / 2;
    SDL_Rect renderQuad = {textX, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void CreditsScene::render() {
    SceneManager& sceneManager = SceneManager::getInstance();
    SDL_Renderer* render = sceneManager.getRenderer();
    if (!render) return;

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    int startY = sceneManager.getHeight() / 6;

    for (size_t i = 0; i < options.size() - 1; ++i) {
        renderText(options[i], startY + (int)i * 35, false);
    }

    renderText(options.back(), sceneManager.getHeight() - 80, selectedIndex == 1);
}

void CreditsScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
}
