#pragma once
#include <SDL.h>
#include <string>
#include "Vector.h"
#include "FontCache.h"

class DamagePopup
{
public:
    DamagePopup();
    
    void init(const std::string &txt, const Vector &pos, SDL_Color col,
              SDL_Renderer *renderer, const char *fontPath, int fontSize,
              int enemyId = -1, float duration = 1.0f);

    void update(float dt);
    void render(SDL_Renderer *renderer, const Vector &cameraOffset);

    bool isAlive() const;
    int getEnemyId() const;

    void appendDamage(int dmg, SDL_Renderer *renderer, const char *fontPath, int fontSize);

private:
    std::string text;
    Vector worldPos;
    SDL_Color color;
    float duration;
    float elapsed;
    bool alive;
    int enemyId;

    SDL_Texture *texture;
    int textW, textH;

    void regenerateTexture(SDL_Renderer *renderer = nullptr, const char *fontPath = nullptr, int fontSize = 12);
};
