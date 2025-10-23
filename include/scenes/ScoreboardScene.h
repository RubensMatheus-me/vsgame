#pragma once

#include "Scene.h"
#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>

class ScoreboardScene : public Scene {
public:
    ScoreboardScene();
    ~ScoreboardScene();

    void init(SDL_Renderer* renderer) override;
    void handleInput(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void cleanUp() override;


private:
	struct PlayerScore {
			std::string name;
			std::string time;
			std::string level;
			std::string enemiesKilled;
		};

    void loadScores();
    void renderText(const std::string& text, int x, int y, SDL_Color color);
	static int timeStringToSeconds(const std::string& timeStr);

    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    std::vector<PlayerScore> scores;
};
