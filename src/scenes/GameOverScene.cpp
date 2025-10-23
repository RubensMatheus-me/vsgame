#include "scenes/GameOverScene.h"
#include "SceneManager.h"
#include "scenes/MenuScene.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>

GameOverScene::GameOverScene(const std::string& time, int level, int enemiesKilled) : timeSurvived(time), level(level), enemiesKilled(enemiesKilled) {}

GameOverScene::~GameOverScene() {
    cleanUp();
}

void GameOverScene::init(SDL_Renderer *renderer_) {
    renderer = renderer_;
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 16);
    if (!font) {
        SDL_Log("Erro ao carregar fonte: %s", TTF_GetError());
    }
}

void GameOverScene::handleInput(SDL_Event& event) {
    if (event.type == SDL_TEXTINPUT) {
        if (nameInput.length() < 10) 
            nameInput += event.text.text;
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_BACKSPACE:
                if (!nameInput.empty())
                    nameInput.pop_back();
                break;
            case SDLK_RETURN:
                if (!saved) {
                    saveScore();
                    saved = true;

                    SceneManager::getInstance().changeScene(new MenuScene());
                }
                break;
            case SDLK_ESCAPE:
                SceneManager::getInstance().changeScene(new MenuScene());
                break;
        }
    }
}

void GameOverScene::update(float dt) {}

void GameOverScene::render() {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};

    renderText("GAME OVER", 100, 50, white);
    renderText("Tempo: " + timeSurvived, 100, 100, white);
    renderText("Digite seu nome:", 100, 150, white);
    renderText(nameInput + "_", 100, 180, yellow);
    renderText("Pressione Enter para salvar", 100, 240, white);
}

void GameOverScene::renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void GameOverScene::saveScore() {
    nlohmann::json scoreData;
    scoreData["nome"] = nameInput;
    scoreData["tempo"] = timeSurvived;
    scoreData["level"] = level;
    scoreData["enemiesKilled"] = enemiesKilled;

    std::ifstream inputFile("score.json");

    nlohmann::json existingData;
    if (inputFile.is_open()) {
        inputFile >> existingData;
        inputFile.close();
    }

    existingData.push_back(scoreData);

    std::ofstream outputFile("score.json");
    if (outputFile.is_open()) {
        outputFile << existingData.dump(4);  
        outputFile.close();
    } else {
        std::cerr << "Erro ao abrir score!" << std::endl;
    }
}

void GameOverScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
