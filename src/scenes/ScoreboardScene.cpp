#include "scenes/ScoreboardScene.h"
#include "SceneManager.h"
#include "scenes/MenuScene.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

ScoreboardScene::ScoreboardScene() {}

ScoreboardScene::~ScoreboardScene() {
    cleanUp();
}

void ScoreboardScene::init(SDL_Renderer* renderer_) {
    renderer = renderer_;
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 14);
    if (!font) {
        std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
    }

    loadScores();
}

void ScoreboardScene::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_ESCAPE) {
            SceneManager::getInstance().changeScene(new MenuScene());
        }
    }
}

void ScoreboardScene::update(float dt) {
    // Nenhuma lógica de atualização necessária
}

void ScoreboardScene::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fundo preto
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};

    renderText("PLACAR", 100, 30, white);

    int y = 80;
    for (const auto& line : scores) {
        renderText(line, 100, y, white);
        y += 25;
    }

    renderText("Pressione ENTER ou ESC para voltar", 50, y + 40, white);

    SDL_RenderPresent(renderer);
}

void ScoreboardScene::renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void ScoreboardScene::loadScores() {
    scores.clear();

    std::ifstream file("placar.txt");
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir placar.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        scores.push_back(line);
    }

    file.close();
}

void ScoreboardScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
