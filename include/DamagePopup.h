#pragma once
#include <SDL.h>
#include <string>
#include "Vector.h"
#include "TextureManager.h"

class DamagePopup
{
public:
    DamagePopup(const std::string &text, const Vector &worldPos, SDL_Color color,
                int enemyId = -1, float duration = 1.0f)
        : text(text), worldPos(worldPos), color(color),
          duration(duration), elapsed(0.0f), alive(true), enemyId(enemyId)
    {
        regenerateTexture();
    }
    void update(float dt)
    {
        elapsed += dt;
        worldPos.y -= 20.0f * dt;
        if (elapsed >= duration)
            alive = false;
    }

    void render(SDL_Renderer *renderer, const Vector &cameraOffset)
    {
        if (!alive || !texture)
            return;
        SDL_Rect dstRect = {
            static_cast<int>(worldPos.x - cameraOffset.x),
            static_cast<int>(worldPos.y - cameraOffset.y),
            textW, textH};
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    }

    bool isAlive() const { return alive; }
    int getEnemyId() const { return enemyId; }

    void appendDamage(int dmg)
    {
        int oldVal = std::stoi(text);
        int newVal = oldVal + dmg;
        text = std::to_string(newVal);
        regenerateTexture();
    }

private:
    std::string text;
    Vector worldPos;
    SDL_Color color;
    float duration;
    float elapsed;
    bool alive;
    int enemyId;

    SDL_Texture *texture = nullptr;
    int textW = 0, textH = 0;

    void regenerateTexture()
    {
        if (texture)
            SDL_DestroyTexture(texture);
        texture = TextureManager::renderText(text, "assets/fonts/dogica.ttf", color, 12);
        SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
    }
};
