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
    static void show(SDL_Renderer* renderer, TTF_Font* font, Player& player, const std::string& upgradesJsonPath, int screenWidth, int screenHeight);
    int lastUpgradedLevel = 1;

private:
    
    static std::vector<Upgrade*> loadUpgradesFromJson(const std::string& path);
    static void applyUpgradeToPlayer(Player& player, const Upgrade& upgrade);
    static int showUpgradeSelection(SDL_Renderer* renderer, TTF_Font* font, const std::vector<Upgrade*>& upgrades, int screenWidth, int screenHeight);
};