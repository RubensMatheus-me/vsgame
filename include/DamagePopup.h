#pragma once
#include <SDL.h>
#include <string>
#include "Vector.h"
#include "FontCache.h"

class DamagePopup
{
public:
    DamagePopup() : alive(false), texture(nullptr) {}

    void init(const std::string &txt, const Vector &pos, SDL_Color col,
              SDL_Renderer *renderer, const char *fontPath, int fontSize,
              int enemyId = -1, float duration = 1.0f)
    {
        text = txt;
        worldPos = pos;
        color = col;
        this->duration = duration;
        elapsed = 0;
        alive = true;
        this->enemyId = enemyId;
        regenerateTexture(renderer, fontPath, fontSize);
    }

    void update(float dt)
    {
        if (!alive)
            return;
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

    void appendDamage(int dmg, SDL_Renderer *renderer, const char *fontPath, int fontSize)
    {
        int oldVal = std::stoi(text);
        int newVal = oldVal + dmg;
        text = std::to_string(newVal);
        regenerateTexture(renderer, fontPath, fontSize);
    }

private:
    std::string text;
    Vector worldPos;
    SDL_Color color;
    float duration;
    float elapsed;
    bool alive;
    int enemyId;

    SDL_Texture *texture;
    int textW = 0, textH = 0;

    void regenerateTexture(SDL_Renderer *renderer = nullptr, const char *fontPath = nullptr, int fontSize = 12)
    {
        if (!renderer || !fontPath)
            return;
        texture = FontCache::getTextTexture(renderer, text, fontPath, color, fontSize);
        SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
    }
};
