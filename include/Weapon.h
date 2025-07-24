#pragma once
#include "Item.h"
#include "SpriteAnimation.h"
#include <vector>
#include "Projectile.h"
#include "MeleeAttack.h" 

class Weapon : public Item {
public:
    Weapon(const Vector& size, SpriteAnimation *spriteAnimation, const std::string& description,
           float flatDamage, float flatAtkSpeed, float damageMultiplier,
           float atkSpeedMultiplier, int level);

    virtual ~Weapon() = default;

	virtual void attack(const Vector& position, const Vector& direction, Entity* owner) = 0;

    float getFlatDamage() const { return this->flatDamage; }
    float getFlatAtkSpeed() const { return this->flatAtkSpeed; }
    float getDamageMultiplier() const { return this->damageMultiplier; }
    float getAtkSpeedMultiplier() const { return this->atkSpeedMultiplier; }
    int getLevel() const { return this->level; }
    SpriteAnimation* getSprite() const { return spriteAnimation; }

	float getTotalDamage() const { return flatDamage * damageMultiplier; }

    void setFlatDamage(float flatDamage) { this->flatDamage = flatDamage; }
    void setFlatAtkSpeed(float flatAtkSpeed) { this->flatAtkSpeed = flatAtkSpeed; }
    void setDamageMultiplier(float damageMultiplier) { this->damageMultiplier = damageMultiplier; }
    void setAtkSpeedMultiplier(float atkSpeedMultiplier) { this->atkSpeedMultiplier = atkSpeedMultiplier; }
    void setLevel(int level) { this->level = level; }

protected:
    SpriteAnimation *spriteAnimation;
    float flatDamage;
    float flatAtkSpeed;
    float damageMultiplier;
    float atkSpeedMultiplier;
    int level;
};
