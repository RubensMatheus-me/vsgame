#pragma once

#include <vector>
#include <string>
#include "Upgrade.h"
#include <nlohmann/json.hpp>
#include "Player.h"
#include <SDL.h>
#include <SDL_ttf.h>

class LevelUpMenu {
public:
    void init(const std::string& jsonPath);
    void show(SDL_Renderer* renderer, TTF_Font* font, Player& player, int screenWidth, int screenHeight);
    int lastUpgradedLevel = 1;
private:
    std::vector<Upgrade*> allUpgrades;

    std::vector<Upgrade*> pickRandomUpgrades(int count);
    int showUpgradeSelection(SDL_Renderer* renderer, TTF_Font* font, const std::vector<Upgrade*>& upgrades, int screenWidth, int screenHeight);
    void applyUpgradeToPlayer(Player& player, const Upgrade& upgrade);
};