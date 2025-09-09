#pragma once
#include "Character.h"
#include "SpriteAnimation.h"
#include "enums/PlayerAnimationState.h"
#include "Upgrade.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Enemy.h"
#include "DamagePopup.h"

class Enemy;
class Weapon;

class Player : public Character
{
public:
    ~Player();
    Player(const Vector &size, SpriteAnimation *spriteAnimation, const Vector &pos, const Vector &speed,
           float hp, float currentHp, float atkRate, float movSpeed, float xp, int level, float xpNextLevel, float atkSpeed,
           bool isMoving, const Vector &direction, float damageCooldown, float invulnerabilityTime);

    void attack(std::vector<std::unique_ptr<Enemy>> &enemies,
                std::vector<std::unique_ptr<DamagePopup>> &popups,
                SDL_Renderer *renderer,
                TTF_Font *font);

    float getXp() const { return this->xp; }
    int getLevel() const { return this->level; }
    float getAtkSpeed() const { return this->atkSpeed; }
    float getAtkRate() const { return this->atkRate; }
    float getDamageCooldown() const { return this->damageCooldown; }
    float getInvunerabilityTime() const { return this->invulnerabilityTime; }
    float getMovSpeed() const { return this->movSpeed; }
    float getXpNextLevel() const { return this->xpNextLevel; }
    PlayerAnimationState getAnimationState() const { return this->currentAnimationState; }
    Vector getPlayerFacingDirection();

    std::vector<std::unique_ptr<Upgrade>> &getUpgrades() { return this->upgrades; }

    void setXp(float xp) { this->xp = xp; }
    void setLevel(int level) { this->level = level; }
    void setAtkSpeed(float atkSpeed) { this->atkSpeed = atkSpeed; }
    void setIsMoving(bool moving) { this->isMoving = moving; }
    void setDirection(const Vector &dir) { this->direction = dir; }
    void setAnimations(SpriteAnimation *anim) { this->spriteAnimation = anim; }
    void setDamageCooldown(float damageCooldown) { this->damageCooldown = damageCooldown; }
    void setMovSpeed(float movSpeed) { this->movSpeed = movSpeed; }

    void setAnimationState(PlayerAnimationState newState);
    void render(SDL_Renderer *renderer) override;
    void update(float deltaTime) override;
    Rect getCollider() const override;

    std::vector<std::unique_ptr<Weapon>> &getWeapons() { return this->weapons; }

private:
    SpriteAnimation *spriteAnimation;
    bool facingRight;
    bool isMoving;
    Vector direction;
    float damageCooldown;
    float invulnerabilityTime;
    float xp;
    float lastHp;
    int level;
    float xpNextLevel;
    float atkSpeed;
    float attackRate;
    PlayerAnimationState currentAnimationState;
    std::vector<std::unique_ptr<Weapon>> weapons;
    bool dead = false;
    float hitAnimTimer = 0.0f;
    std::vector<std::unique_ptr<Upgrade>> upgrades;
};