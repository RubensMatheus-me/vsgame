#pragma once
#include <string>
#include "Vector.h"
#include <SDL.h>
#include <SDL_ttf.h>
class DamagePopup
{
public:
    DamagePopup(SDL_Renderer *renderer, TTF_Font *font, const Vector &pos, int damage)
        : position(pos), damage(damage), lifetime(1.0f), velocity(0, -50.0f), texture(nullptr)
    {
        SDL_Color color = {255, 0, 0, 255};
        std::string dmgText = std::to_string(damage);

        SDL_Surface *surface = TTF_RenderText_Solid(font, dmgText.c_str(), color);
        if (surface)
        {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            width = surface->w;
            height = surface->h;
            SDL_FreeSurface(surface);
        }
    }

    ~DamagePopup()
    {
        if (texture)
            SDL_DestroyTexture(texture);
    }

    void update(float deltaTime)
    {
        lifetime -= deltaTime;
        position = position + velocity * deltaTime;
    }

    void render(SDL_Renderer *renderer)
    {
        if (lifetime <= 0.0f || !texture)
            return;

        SDL_Rect dst = {(int)position.x, (int)position.y, width, height};
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    }

    bool isAlive() const { return lifetime > 0.0f; }

private:
    Vector position;
    Vector velocity;
    int damage;
    float lifetime;
    SDL_Texture *texture;
    int width;
    int height;
};
