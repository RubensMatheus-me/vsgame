#pragma once
#include "Item.h"

class Upgrade : public Item
{
public:
    Upgrade(const Vector &size, SpriteAnimation *spriteAnimation, const std::string &name, const std::string &description,
            float hpMultiplier, float damageMultiplier, float movSpeedMultiplier);

    float getHpMultiplier() const { return this->hpMultiplier; }
    float getDamageMultiplier() const { return this->damageMultiplier; }
    float getMovSpeedMultiplier() const { return this->movSpeedMultiplier; }
    std::string getName() const { return this->name; }

    void setHpMultiplier(float hpMultiplier) { this->hpMultiplier = hpMultiplier; }
    void setDamageMultiplier(float damageMultiplier) { this->damageMultiplier = damageMultiplier; }
    void setMovSpeedMultiplier(float movSpeedMultiplier) { this->movSpeedMultiplier = movSpeedMultiplier; }
    void render(SDL_Renderer *renderer, const Vector &position);
    void render(SDL_Renderer *renderer) override;
    void update(float deltaTime) override;

private:
    float hpMultiplier;
    float damageMultiplier;
    float movSpeedMultiplier;
    std::string name;
};
