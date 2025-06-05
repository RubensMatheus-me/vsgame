#include "LevelUpMenu.h"
#include <fstream>
#include <random>
#include "Vector.h"
#include "SpriteAnimation.h"
#include "TextureManager.h"

void LevelUpMenu::init(const std::string& jsonPath) {
    using json = nlohmann::json;
    std::ifstream file(jsonPath);
    if (!file.is_open()) return;

    json jsonData;
    file >> jsonData;

    for (auto& entry : jsonData) {
        std::string name = entry.value("name", "");
        std::string desc = entry.value("description", "");
        float hpMult = entry.value("hpMultiplier", 1.0f);
        float dmgMult = entry.value("damageMultiplier", 1.0f);
        float movMult = entry.value("movSpeedMultiplier", 1.0f);
        
        SpriteAnimation* anim = new SpriteAnimation();
        anim->addAnimation("idle", name, 0, 0, 32, 32, 1);
        anim->play("idle");
        allUpgrades.push_back(new Upgrade({64, 64}, anim, name, desc, hpMult, dmgMult, movMult));
    }
}

std::vector<Upgrade*> LevelUpMenu::pickRandomUpgrades(int count) {
    std::vector<Upgrade*> picked;
    std::vector<int> indices(allUpgrades.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

    for (int i = 0; i < count && i < indices.size(); ++i) {
        picked.push_back(allUpgrades[indices[i]]);
    }
  
    return picked;
}

void LevelUpMenu::show(SDL_Renderer* renderer, TTF_Font* font, Player& player, int screenWidth, int screenHeight) {
    std::vector<Upgrade*> upgrades = pickRandomUpgrades(3);

    if (upgrades.empty()) return;
    int selectedIndex = showUpgradeSelection(renderer, font, upgrades, screenWidth, screenHeight);
    if (selectedIndex != -1) {
        applyUpgradeToPlayer(player, *upgrades[selectedIndex]);
    }
}

void LevelUpMenu::applyUpgradeToPlayer(Player& player, const Upgrade& upgrade) {
    player.setHp(player.getHp() * upgrade.getHpMultiplier());
    player.setAtkSpeed(player.getAtkSpeed() * upgrade.getDamageMultiplier());
    player.setMovSpeed(player.getMovSpeed() * upgrade.getMovSpeedMultiplier());
	player.getUpgrades().push_back(std::make_unique<Upgrade>(upgrade));
}

int LevelUpMenu::showUpgradeSelection(SDL_Renderer* renderer, TTF_Font* font, const std::vector<Upgrade*>& upgrades, int screenWidth, int screenHeight) {
    bool running = true;
    int selected = 0;
    SDL_Event e;

    SDL_Texture* menuTexture = TextureManager::getTexture("upgradeMenu");
    const int menuWidth = 407;
    const int menuHeight = 520;
    const int upgradeBoxHeight = (menuHeight / 5);
    const int upgradeAreaY = menuWidth / 3;

    int menuX = (screenWidth - menuWidth) / 2;
    int menuY = (screenHeight - menuHeight) / 2;

    const int itemCount = std::min<int>(3, upgrades.size());

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return -1;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP: selected = (selected + itemCount - 1) % itemCount; break;
                    case SDLK_DOWN: selected = (selected + 1) % itemCount; break;
                    case SDLK_RETURN: return selected;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect menuRect = {menuX, menuY, menuWidth, menuHeight};
        SDL_RenderCopy(renderer, menuTexture, nullptr, &menuRect);

        for (int i = 0; i < itemCount; ++i) {
            int boxY = upgradeAreaY + i * upgradeBoxHeight;

            std::cout << upgrades[i]->getName() << std::endl;

            upgrades[i]->render(renderer, Vector((float)(menuX + 20), (float)(boxY + 10)));

            std::string text = upgrades[i]->getDescription();

            SDL_Color color = {255, 255, 255}; 

            if (i == selected) {
                color = {255, 255, 0}; 
            }

            SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, 340);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect dst = {menuX + 80, boxY + 10, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &dst);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return -1;
}
