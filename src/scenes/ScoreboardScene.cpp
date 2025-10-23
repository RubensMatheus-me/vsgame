#include "scenes/ScoreboardScene.h"
#include "SceneManager.h"
#include "scenes/MenuScene.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <algorithm>

ScoreboardScene::ScoreboardScene() {}

ScoreboardScene::~ScoreboardScene() {
    cleanUp();
}

int ScoreboardScene::timeStringToSeconds(const std::string& timeStr) {
    if (timeStr.size() < 4) return 0;
    int minutes = std::stoi(timeStr.substr(0, 2));
    int seconds = std::stoi(timeStr.substr(3, 2));
    return minutes * 60 + seconds;
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

void ScoreboardScene::update(float dt) {}

void ScoreboardScene::render() {
    SceneManager& sceneManager = SceneManager::getInstance();
    int screenWidth = sceneManager.getWidth();
    int screenHeight = sceneManager.getHeight();

    const float marginX = screenWidth * 0.15f;
    const float tableWidth = screenWidth * 0.70f;
    const int columnCount = 4;
    const float columnWidth = tableWidth / columnCount;
    const float headerY = screenHeight * 0.2f;
    const float startY = screenHeight * 0.3f;
    const int rowSpacing = 25;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};

    renderText("PLACAR", marginX, screenHeight * 0.1f, white);

    std::vector<std::string> headers = {"NOME", "TEMPO", "LEVEL", "ENEMIES"};
    for (size_t i = 0; i < headers.size(); ++i) {
        renderText(headers[i], marginX + i * columnWidth, headerY, white);
    }

    float y = startY;
    for (const auto& score : scores) {
        std::vector<std::string> row = {
            score.name,
            score.time,
            score.level,
            score.enemiesKilled
        };
        for (size_t i = 0; i < row.size(); ++i) {
            renderText(row[i], marginX + i * columnWidth, y, white);
        }
        y += rowSpacing;
    }

    renderText("Pressione ENTER ou ESC para voltar", marginX, y + 40, white);
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

    std::ifstream file("score.json");
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir score.json" << std::endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    for (const auto& record : jsonData) {
        std::string name = record["nome"].is_string() ? record["nome"].get<std::string>() : "";
        std::string time = record["tempo"].is_string() ? record["tempo"].get<std::string>() : "";
        std::string level = std::to_string(record["level"].get<int>());

        int enemiesKilledInt = 0;
        if (record["enemiesKilled"].is_number_integer()) {
            enemiesKilledInt = record["enemiesKilled"].get<int>();
        } else if (record["enemiesKilled"].is_number_float()) {
            enemiesKilledInt = static_cast<int>(record["enemiesKilled"].get<float>());
        }

        std::string enemiesKilled = std::to_string(enemiesKilledInt);
        scores.push_back({name, time, level, enemiesKilled});
    }

    std::sort(scores.begin(), scores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        return timeStringToSeconds(a.time) > timeStringToSeconds(b.time);
    });

    if (scores.size() > 10) {
        scores.resize(10);
    }
}


void ScoreboardScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

