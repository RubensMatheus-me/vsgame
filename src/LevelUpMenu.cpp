#include "LevelUpMenu.h"
#include <fstream>
#include "Vector.h"
#include "SpriteAnimation.h"

void LevelUpMenu::show(SDL_Renderer* renderer, TTF_Font* font, Player& player, const std::string& upgradesJsonPath, int screenWidth, int screenHeight) {
    std::vector<Upgrade*> upgrades = loadUpgradesFromJson(upgradesJsonPath);
    int selectedIndex = showUpgradeSelection(renderer, font, upgrades, screenWidth, screenHeight);

    if (selectedIndex != -1) {
        applyUpgradeToPlayer(player, *upgrades[selectedIndex]);
    }

    for (auto* u : upgrades) delete u;
}

std::vector<Upgrade*> LevelUpMenu::loadUpgradesFromJson(const std::string& path) {
    using json = nlohmann::json;
    std::ifstream file(path);

    json jsonData;
    file >> jsonData;

    std::vector<Upgrade*> upgrades;

    for (auto& entry : jsonData) {
        std::string desc = entry["description"];
        float hpMult = entry.value("hpMultiplier", 1.0f);
        float dmgMult = entry.value("damageMultiplier", 1.0f);
        float movMult = entry.value("movSpeedMultiplier", 1.0f);

        SpriteAnimation* anim = new SpriteAnimation();
        anim->addAnimation("idle", "slime", 0, 0, 32, 32, 1);
        anim->play("idle");

        upgrades.push_back(new Upgrade({64, 64}, anim, desc, hpMult, dmgMult, movMult));
    }

    return upgrades;
}

void LevelUpMenu::applyUpgradeToPlayer(Player& player, const Upgrade& upgrade) {
    player.setHp(player.getHp() * upgrade.getHpMultiplier());
    player.setAtkSpeed(player.getAtkSpeed() * upgrade.getDamageMultiplier());
    player.setMovSpeed(player.getMovSpeed() * upgrade.getMovSpeedMultiplier());
}

int LevelUpMenu::showUpgradeSelection(SDL_Renderer* renderer, TTF_Font* font, const std::vector<Upgrade*>& upgrades, int screenWidth, int screenHeight) {
    bool running = true;
    int selected = 0;
    SDL_Event e;

    const int itemHeight = 100;
    const int spriteWidth = 64;
    const int spriteHeight = 64;
    const int spacing = 20;

    int totalListHeight = upgrades.size() * itemHeight;
    int startY = (screenHeight - totalListHeight) / 2;
    const int totalItemWidth = spriteWidth + spacing + 300;
    const int startX = (screenWidth - totalItemWidth) / 2;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return -1;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        selected = (selected + upgrades.size() - 1) % upgrades.size();
                        break;
                    case SDLK_DOWN:
                        selected = (selected + 1) % upgrades.size();
                        break;
                    case SDLK_RETURN:
                        return selected;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < upgrades.size(); ++i) {
            int y = startY + static_cast<int>(i) * itemHeight;

            Vector menuOffset(startX, static_cast<float>(y + (itemHeight - spriteHeight) / 2));
            upgrades[i]->render(renderer, menuOffset);

            SDL_Color color = (i == selected) ? SDL_Color{255, 255, 0} : SDL_Color{255, 255, 255};
            const std::string& text = upgrades[i]->getDescription();

            SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_Rect dst = {
                startX + spriteWidth + spacing,
                y + (itemHeight - surface->h) / 2,
                surface->w,
                surface->h
            };
            SDL_RenderCopy(renderer, texture, nullptr, &dst);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return -1;
}