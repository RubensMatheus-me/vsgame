#include "scenes/MenuScene.h"
#include "SceneManager.h"
#include "scenes/ConfigScene.h"
#include "scenes/ScoreboardScene.h"
#include "GameStateManager.h"
#include "enums/GameState.h"
#include <iostream>
#include <SDL_image.h>

MenuScene::MenuScene() {}

MenuScene::~MenuScene() {
    cleanUp(); 
}

void MenuScene::init(SDL_Renderer *render) {
    renderer = render;
    TTF_CloseFont(font);
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 16);
    if (!font) {
        std::cerr << "Erro ao carregar a fonte: " << TTF_GetError() << std::endl;
    }
    SDL_Surface* bgSurface = IMG_Load("assets/cenas/menuPrincipal.png");
    if (!bgSurface) {
        std::cerr << "Erro ao carregar imagem de fundo: " << IMG_GetError() << std::endl;
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
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
            case SDLK_LEFT:
                selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                break;
            case SDLK_RIGHT:
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

    if (backgroundTexture) {
    SDL_SetTextureAlphaMod(backgroundTexture, 90); 
    SDL_Rect destRect = {0, 0, sceneManager.getWidth(), sceneManager.getHeight()};
    SDL_RenderCopy(sceneManager.getRenderer(), backgroundTexture, nullptr, &destRect);
	} else {
        SDL_SetRenderDrawColor(sceneManager.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(sceneManager.getRenderer());
    }

    int startY = sceneManager.getHeight() / 2 - (int)options.size() * 30;

	for (size_t i = 0; i < options.size(); ++i) {
        renderText(options[i], sceneManager.getWidth() * (i*0.30), sceneManager.getWidth()*0.6, i == selectedIndex);
    }
	
}

void MenuScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
}