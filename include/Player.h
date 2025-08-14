#pragma once
#include "Character.h"
#include "SpriteAnimation.h"
#include "enums/PlayerAnimationState.h"
#include "MeleeWeapon.h"
#include "RangedWeapon.h"
#include "Upgrade.h"
#include <vector>
#include <string>
#include <iostream>

class Player : public Character {
    public:
    Player(const Vector& size, SpriteAnimation* spriteAnimation, const Vector& pos, const Vector& speed,
        float hp, float currentHp, float atkRate, float movSpeed, float xp, int level, float xpNextLevel, float atkSpeed,
        bool isMoving, const Vector& direction, float damageCooldown, float invulnerabilityTime);
    
        float getXp() const { return this->xp; }
        int getLevel() const { return this->level; }
        float getAtkSpeed() const { return this->atkSpeed; }
        float getDamageCooldown() const { return this->damageCooldown; }
        float getInvunerabilityTime() const { return this->invulnerabilityTime; }
        float getMovSpeed() const { return this->movSpeed; }
        float getXpNextLevel() const { return this->xpNextLevel; }
        PlayerAnimationState getAnimationState() const { return this->currentAnimationState; }
		Vector getPlayerFacingDirection();

		std::vector<std::unique_ptr<Upgrade>>& getUpgrades() { return this->upgrades; }
    
        void setXp(float xp) { this->xp = xp; }
        void setLevel(int level) { this->level = level; }
        void setAtkSpeed(float atkSpeed) { this->atkSpeed = atkSpeed; }
        void setIsMoving(bool moving) { this->isMoving = moving; }
        void setDirection(const Vector& dir) { this->direction = dir; }
        void setAnimations(SpriteAnimation* anim) {this->spriteAnimation = anim;}
        void setDamageCooldown(float damageCooldown) { this->damageCooldown = damageCooldown; }
        void setMovSpeed(float movSpeed) { this->movSpeed = movSpeed; }

		void setAnimationState(PlayerAnimationState newState);
        void render(SDL_Renderer* renderer) override;
        void update(float deltaTime) override;
        Rect getCollider() const override;
    
        bool canAttack() const { return attackCooldown <= 0;}
        void resetAttackCooldown() {attackCooldown = attackRate;}
		std::vector<std::unique_ptr<MeleeWeapon>>& getMeleeWeapons() { return this->meleeWeapons; }
		std::vector<std::unique_ptr<RangedWeapon>>& getRangedWeapons() { return this->rangedWeapons; }
		
    private:
        SpriteAnimation* spriteAnimation;
        bool facingRight;
        bool isMoving;
        Vector direction;
        float damageCooldown;
        float invulnerabilityTime;
        float xp;
        int level;
        float xpNextLevel;
        float atkSpeed;
        float attackCooldown = 0.0f;  
        float attackRate;  
		PlayerAnimationState currentAnimationState;          
		std::vector<std::unique_ptr<MeleeWeapon>> meleeWeapons;
		std::vector<std::unique_ptr<RangedWeapon>> rangedWeapons;
		std::vector<std::unique_ptr<Upgrade>> upgrades;

};