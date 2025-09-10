#include "Upgrade.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"

Upgrade::Upgrade(const Vector &size, SpriteAnimation *spriteAnimation, const std::string &name, const std::string &description,
                 float hpMultiplier, float damageMultiplier, float movSpeedMultiplier, float attackRateMultiplier)
    : Item(size, spriteAnimation, description),
      hpMultiplier(hpMultiplier), damageMultiplier(damageMultiplier), movSpeedMultiplier(movSpeedMultiplier), attackRateMultiplier(attackRateMultiplier) {}

void Upgrade::render(SDL_Renderer *renderer, const Vector &position)
{

    if (getSprite())
    {
        const int ICON_SIZE = 29;

        SDL_Rect destRect = {
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            ICON_SIZE,
            ICON_SIZE};

        SDL_Rect srcRect = getSprite()->getCurrentFrameRect();

        SDL_Texture *texture = TextureManager::getTexture(getSprite()->getCurrentTextureName());
        SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void Upgrade::render(SDL_Renderer *renderer)
{

    if (getSprite())
    {
        getSprite()->render(renderer, 1, 1);
    }
}

void Upgrade::update(float deltaTime)
{
    if (getSprite())
    {
        getSprite()->update(deltaTime);
    }
}