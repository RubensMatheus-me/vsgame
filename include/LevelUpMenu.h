#pragma once

#include <vector>
#include <string>
#include "Upgrade.h"
#include <nlohmann/json.hpp>
#include "Player.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "SpriteAnimation.h"
#include "ChoiceItem.h"
#include "WeaponChoice.h"

class LevelUpMenu
{

public:
    void init(const std::string &upgradePath, const std::string &weaponPath);
	void initUpgrades(const std::string &jsonPath);
	void initWeapons(const std::string &jsonPath);

    void show(SDL_Renderer *renderer, TTF_Font *font, Player &player, int screenWidth, int screenHeight);
    int lastUpgradedLevel = 1;

private:
    std::vector<Upgrade *> allUpgrades;
	std::vector<WeaponChoice *> allWeapons;

    std::vector<std::unique_ptr<ChoiceItem>> pickRandom(int count);
	void applyToPlayer(Player &player, ChoiceItem &choice);
	void resolveWeapon(Player &player, WeaponChoice* weaponChoice);
	int showUpgradeSelection(SDL_Renderer* renderer, TTF_Font* font,const std::vector<std::unique_ptr<ChoiceItem>>& choices,int screenWidth, int screenHeight);
    void applyUpgradeToPlayer(Player &player, const Upgrade &upgrade);
};

