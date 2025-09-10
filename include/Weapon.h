#pragma once

#include "Vector.h"
#include <memory>
#include <vector>
#include <string>
#include "Item.h"
#include "SpriteAnimation.h"
#include "Attack.h"

class Enemy;
class Player;

class Weapon : public Item {
public:
    Weapon(const Vector& size, SpriteAnimation *spriteAnimation, const std::string& description,
           float flatDamage, float flatAtkSpeed, float damageMultiplier,
           float atkSpeedMultiplier, int level, float cooldown, int id, float knockback);

    virtual ~Weapon() = default;

    void update(float deltaTime) override;

    virtual void attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies,Player *player) = 0;  
    virtual void levelUp(int levelUp) = 0;

    float getFlatDamage() const { return this->flatDamage; }
    float getFlatAtkSpeed() const { return this->flatAtkSpeed; }
    float getDamageMultiplier() const { return this->damageMultiplier; }
    float getAtkSpeedMultiplier() const { return this->atkSpeedMultiplier; }
    int getLevel() const { return this->level; }
    float getCurrentCooldown() const { return this->currentCooldown; }
    int getId() const { return this->id; }
    float getknockback() const { return this->knockback; }

    SpriteAnimation* getSprite() const { return spriteAnimation; }
    std::vector<std::unique_ptr<Attack>>& getAttacks() { return attacks; }

    float getTotalDamage() const { return flatDamage * damageMultiplier; }

    void setFlatDamage(float flatDamage) { this->flatDamage = flatDamage; }
    void setFlatAtkSpeed(float flatAtkSpeed) { this->flatAtkSpeed = flatAtkSpeed; }
    void setDamageMultiplier(float damageMultiplier) { this->damageMultiplier = damageMultiplier; }
    void setAtkSpeedMultiplier(float atkSpeedMultiplier) { this->atkSpeedMultiplier = atkSpeedMultiplier; }
    void setLevel(int level) { this->level = level; }

    float resolveDamage(Player* player); 

protected:
    float flatDamage;
    float flatAtkSpeed;
    float damageMultiplier;
    float atkSpeedMultiplier;
    int level;
    float cooldown;
    float currentCooldown;
    std::vector<std::unique_ptr<Attack>> attacks;
    int id;
    float knockback;
};
