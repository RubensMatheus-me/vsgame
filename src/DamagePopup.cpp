#include "DamagePopup.h"
#include <SDL_ttf.h>
#include <iostream>

DamagePopup::DamagePopup()
    : alive(false), texture(nullptr), textW(0), textH(0), enemyId(-1), duration(1.0f), elapsed(0) {}

void DamagePopup::init(const std::string &txt, const Vector &pos, SDL_Color col,
                       SDL_Renderer *renderer, const char *fontPath, int fontSize,
                       int enemyId, float duration)
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

void DamagePopup::update(float dt)
{
    if (!alive) return;
    elapsed += dt;
    worldPos.y -= 20.0f * dt;
    if (elapsed >= duration)
        alive = false;
}

void DamagePopup::render(SDL_Renderer *renderer, const Vector &cameraOffset)
{
    if (!alive || !texture) return;

    SDL_Rect dstRect = {
        static_cast<int>(worldPos.x - cameraOffset.x),
        static_cast<int>(worldPos.y - cameraOffset.y),
        textW, textH
    };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

bool DamagePopup::isAlive() const { return alive; }
int DamagePopup::getEnemyId() const { return enemyId; }

void DamagePopup::appendDamage(int dmg, SDL_Renderer *renderer, const char *fontPath, int fontSize)
{
    int oldVal = std::stoi(text);
    int newVal = oldVal + dmg;
    text = std::to_string(newVal);
    regenerateTexture(renderer, fontPath, fontSize);
}

void DamagePopup::regenerateTexture(SDL_Renderer *renderer, const char *fontPath, int fontSize)
{
    if (!renderer || !fontPath) return;

    texture = FontCache::getTextTexture(renderer, text, fontPath, color, fontSize);
    if (texture)
        SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
}
