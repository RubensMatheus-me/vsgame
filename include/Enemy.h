#pragma once
#include <memory>
#include "Character.h"
#include "Player.h"
#include "SpriteAnimation.h"

class Enemy : public Character
{
public:
    Enemy(const Vector &size, SpriteAnimation *spriteAnimation, std::unique_ptr<SpriteAnimation> anim, const Vector &pos, const Vector &speed,
          float hp, float currentHp, float atkRate, float movSpeed, float xpDrop, int spawnWeigh, float baseAtk);

    void setTarget(const Player *newTarget) { this->target = newTarget; }

    float getXpDrop() const { return this->xpDrop; }
    int getSpawnWeight() const { return this->spawnWeight; }

    void setXpDrop(float xpDrop) { this->xpDrop = xpDrop; }
    void setSpawnWeight(int spawnWeight) { this->spawnWeight = spawnWeight; }

    float getBaseAtk() { return this->baseAtk; }

    void render(SDL_Renderer *renderer) override;
    void update(float deltaTime) override;

    Rect getCollider() const override;
    void setAlive(bool val) { alive = val; }
    bool isAlive() const { return alive; }

private:
    bool alive = true;
    SpriteAnimation *spriteAnimation;
    std::unique_ptr<SpriteAnimation> animation;
    const Player *target;
    float xpDrop;
    int spawnWeight;
    float baseAtk;
};