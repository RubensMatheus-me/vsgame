#pragma once
#include "Character.h"
#include "SpriteAnimation.h"
#include <vector>
#include <string>

class Player : public Character {
    public:
    Player(const Vector& size, SpriteAnimation* spriteAnimation, const Vector& pos, const Vector& speed,
        float hp, float atkRate, float movSpeed, float xp, int level, float atkSpeed,
        bool isMoving, Vector& direction, float damageCooldown, float invulnerabilityTime);
    
        float getXp() const { return this->xp; }
        int getLevel() const { return this->level; }
        float getAtkSpeed() const { return this->atkSpeed; }
        float getDamageCooldown() const { return this->damageCooldown; }
        float getInvunerabilityTime() const { return this->invulnerabilityTime; }
    
        void setXp(float xp) { this->xp = xp; }
        void setLevel(int level) { this->level = level; }
        void setAtkSpeed(float atkSpeed) { this->atkSpeed = atkSpeed; }
        void setIsMoving(bool moving) { this->isMoving = moving; }
        void setDirection(const Vector& dir) { this->direction = dir; }
        void setAnimations(SpriteAnimation* anim) {this->spriteAnimation = anim;}
        void setDamageCooldown(float damageCooldown) { this->damageCooldown = damageCooldown; }

        void render(SDL_Renderer* renderer, const Vector& cameraOffSet) override;
        void update(float deltaTime) override;
        Rect getCollider() const override;
    
    private:
        SpriteAnimation* spriteAnimation;
        bool facingRight;
        bool isMoving;
        Vector direction;
        float damageCooldown;
        float invulnerabilityTime;
        float xp;
        int level;
        float atkSpeed;
};
