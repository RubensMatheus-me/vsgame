#include "LevelUpMenu.h"
#include <fstream>
#include <random>
#include "Vector.h"
#include "SpriteAnimation.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameStateManager.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include "UpgradeChoiceItem.h"
#include "WeaponChoiceItem.h"
#include "Axe.h"
#include "BrassKnuckles.h"
#include "Config.h"
#include "Chakram.h"

using namespace Config;

void LevelUpMenu::init(const std::string &upgradePath, const std::string &weaponPath)
{
	initUpgrades(upgradePath);
	initWeapons(weaponPath);
}

void LevelUpMenu::initUpgrades(const std::string &jsonPath) {
    using json = nlohmann::json;
    std::ifstream file(jsonPath);
    if (!file.is_open())
        return;

    json jsonData;
    file >> jsonData;

    for (auto &entry : jsonData)
    {
        std::string name = entry.value("name", "");
        std::string desc = entry.value("description", "");
        float hpMult = entry.value("hpMultiplier", 1.0f);
        float dmgMult = entry.value("damageMultiplier", 1.0f);
        float movMult = entry.value("movSpeedMultiplier", 1.0f);

        SpriteAnimation *anim = new SpriteAnimation();
        anim->addAnimation("idle", name, 0, 0, 32, 32, 1, true);
        anim->play("idle");
        allUpgrades.push_back(new Upgrade({64, 64}, anim, name, desc, hpMult, dmgMult, movMult));
    }
}

void LevelUpMenu::initWeapons(const std::string &jsonPath) {
	using json = nlohmann::json;
    std::ifstream file(jsonPath);
    if (!file.is_open())
        return;

    json jsonData;
    file >> jsonData;

    for (auto &entry : jsonData)
    {
		int id = entry.value("id", 0);
        std::string name = entry.value("name", "");
        std::string desc = entry.value("description", "");
        std::string spriteName = entry.value("spriteName", "");

        SpriteAnimation *anim = new SpriteAnimation();
        anim->addAnimation("idle", spriteName, 0, 0, 32, 32, 1, true);
        anim->play("idle");
        allWeapons.push_back(new WeaponChoice(id, name, desc, anim));
    }
}

std::vector<std::unique_ptr<ChoiceItem>> LevelUpMenu::pickRandom(int count)
{
	std::vector<std::unique_ptr<ChoiceItem>> choices;

	for (int i = 0; i < 3; ++i)
	{
		bool pickUpgrade = rand() % 2;

		if (pickUpgrade && !allUpgrades.empty())
		{
			int idx = rand() % allUpgrades.size();
			choices.push_back(std::make_unique<UpgradeChoiceItem>(allUpgrades[idx]));
		}
		else if (!allWeapons.empty())
		{
			int idx = rand() % allWeapons.size();
			choices.push_back(std::make_unique<WeaponChoiceItem>(allWeapons[idx]));
		}
	}

	return choices;
}

void LevelUpMenu::show(SDL_Renderer *renderer, TTF_Font *font, Player &player, int screenWidth, int screenHeight)
{
    std::vector<std::unique_ptr<ChoiceItem>> choices = pickRandom(3);
    int selectedIndex = showUpgradeSelection(renderer, font, choices, screenWidth, screenHeight);
    if (selectedIndex != -1)
    {
        applyToPlayer(player, *choices[selectedIndex]);
    }
}

void LevelUpMenu::applyToPlayer(Player &player, ChoiceItem &choice) {

	if (choice.isWeapon()) {
		auto* weaponItem = dynamic_cast<WeaponChoiceItem*>(&choice);
		resolveWeapon(player, weaponItem->getWeapon());

	} else {
		auto* upgradeItem = dynamic_cast<UpgradeChoiceItem*>(&choice);
		Upgrade* upgrade = upgradeItem->getUpgrade();
		applyUpgradeToPlayer(player, *upgrade);
	}
}

void LevelUpMenu::resolveWeapon(Player &player, WeaponChoice* weaponChoice) {
    int idWeapon = weaponChoice->id;

    for (auto& weapon : player.getWeapons()) {
        if (idWeapon == weapon->getId()) {
            weapon->levelUp(1);
            return;
        }
    }

    switch (weaponChoice->id) {
        case 1: {
            auto anim = std::make_unique<SpriteAnimation>();
            anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
            anim->play("axe-idle");
            std::unique_ptr<Weapon> weapon = std::make_unique<Axe>(
                Config::PLAYER_SIZE,
                anim.get(),
                "Machado"
            );
            player.getWeapons().push_back(std::move(weapon));
            break;
        }

        case 2: {
            auto anim = std::make_unique<SpriteAnimation>();
            anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
            anim->addAnimation("axe-right", "axe", 0, 0, 32, 32, 5, true);
            anim->addAnimation("axe-left", "axe", 160, 0, 32, 32, 5, true);
            anim->play("axe-right");
            std::string desc = "teste";
            std::unique_ptr<Weapon> weapon = std::make_unique<BrassKnuckles>(
                Config::PLAYER_SIZE,
                anim.get(),
                desc,
                50.0f,
                50.0f,
                1.0f,
                1.0f,
                1,
                3.0f,
                2,
                600.0f
            );
            player.getWeapons().push_back(std::move(weapon));
            break;
        }
        case 3: {
            auto anim = std::make_unique<SpriteAnimation>();
            anim->addAnimation("chakram-idle", "Chakram", 0, 0, 32, 32, 1, false);
            anim->play("chakram-idle");
            std::unique_ptr<Weapon> weapon = std::make_unique<Chakram>(
                Config::PLAYER_SIZE,
                anim.get(),
                "Chakram"
            );
            player.getWeapons().push_back(std::move(weapon));
            break;
        }
    }
}

void LevelUpMenu::applyUpgradeToPlayer(Player &player, const Upgrade &upgrade)
{
    player.setHp(player.getHp() * upgrade.getHpMultiplier());
    player.setAtkSpeed(player.getAtkSpeed() * upgrade.getDamageMultiplier());
    player.setMovSpeed(player.getMovSpeed() * upgrade.getMovSpeedMultiplier());
    player.getUpgrades().push_back(std::make_unique<Upgrade>(upgrade));
}

int LevelUpMenu::showUpgradeSelection(SDL_Renderer* renderer, TTF_Font* font, const std::vector<std::unique_ptr<ChoiceItem>>& choices, int screenWidth, int screenHeight)
{
    if (choices.empty()) return -1;
    bool running = true;
    int selected = 0;
    SDL_Event e;

    SDL_Texture* menuTexture = TextureManager::getTexture("upgradeMenu");

    const int menuWidth = 407;
    const int menuHeight = 520;
    const int ICON_SIZE = 32;
    const int ITEM_START_Y = 150;
    const int ITEM_SPACING = 140;
    const int ICON_X = 30;
    const int TEXT_X = ICON_X + ICON_SIZE + 20;
    const int HORIZONTAL_TEXT_OFFSET = 20;

    int menuX = (screenWidth - menuWidth) / 2;
    int menuY = (screenHeight - menuHeight) / 2;
    const int itemCount = std::min<int>(3, choices.size());

    SDL_SetTextureBlendMode(menuTexture, SDL_BLENDMODE_BLEND);

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                GameStateManager::getInstance().setState(GameState::InLose);
                return -1;
            }

            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    selected = (selected + itemCount - 1) % itemCount;
                    break;
                case SDLK_DOWN:
                    selected = (selected + 1) % itemCount;
                    break;
                case SDLK_RETURN:
                    return selected;
                }
            }
        }

        SDL_Rect menuRect = { menuX, menuY, menuWidth, menuHeight };
        SDL_RenderCopy(renderer, menuTexture, nullptr, &menuRect);

        for (int i = 0; i < itemCount; ++i)
        {
            int itemY = menuY + ITEM_START_Y + i * ITEM_SPACING;
            int iconY = itemY - ICON_SIZE / 2;

            choices[i]->render(renderer, Vector((float)(menuX + ICON_X), (float)iconY));

            std::string text = choices[i]->getDescription();
            SDL_Color color = (i == selected) ? SDL_Color{255, 255, 0} : SDL_Color{255, 255, 255};

            SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, 300);
            if (surface)
            {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture)
                {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

                    int textY = itemY - surface->h / 2;
                    SDL_Rect dst = { menuX + TEXT_X, textY + HORIZONTAL_TEXT_OFFSET, surface->w, surface->h };
                    SDL_RenderCopy(renderer, texture, nullptr, &dst);

                    SDL_DestroyTexture(texture);
                }
                SDL_FreeSurface(surface);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return -1;
}
