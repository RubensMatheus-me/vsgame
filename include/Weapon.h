#pragma once

#include "Item.h"
#include "SpriteAnimation.h"
#include <vector>
#include "Attack.h"

class Player;

class Weapon : public Item {
public:
    Weapon(const Vector& size, SpriteAnimation *spriteAnimation, const std::string& description,
           float flatDamage, float flatAtkSpeed, float damageMultiplier,
           float atkSpeedMultiplier, int level, float cooldown);
           
     virtual ~Weapon() = default;

    void update(float deltaTime) override;

	virtual void attack(const Vector& position, const Vector& direction, Player* owner) = 0;

    float getFlatDamage() const { return this->flatDamage; }
    float getFlatAtkSpeed() const { return this->flatAtkSpeed; }
    float getDamageMultiplier() const { return this->damageMultiplier; }
    float getAtkSpeedMultiplier() const { return this->atkSpeedMultiplier; }
    int getLevel() const { return this->level; }
    float getCurrentCooldown() const { return this->currentCooldown; }

    SpriteAnimation* getSprite() const { return spriteAnimation; }
    std::vector<std::unique_ptr<Attack>>& getAttacks() { return attacks; }

	float getTotalDamage() const { return flatDamage * damageMultiplier; }

    void setFlatDamage(float flatDamage) { this->flatDamage = flatDamage; }
    void setFlatAtkSpeed(float flatAtkSpeed) { this->flatAtkSpeed = flatAtkSpeed; }
    void setDamageMultiplier(float damageMultiplier) { this->damageMultiplier = damageMultiplier; }
    void setAtkSpeedMultiplier(float atkSpeedMultiplier) { this->atkSpeedMultiplier = atkSpeedMultiplier; }
    void setLevel(int level) { this->level = level; }

protected:
    float flatDamage;
    float flatAtkSpeed;
    float damageMultiplier;
    float atkSpeedMultiplier;
    int level;
    float cooldown;
    float currentCooldown;
    std::vector<std::unique_ptr<Attack>> attacks;
};
