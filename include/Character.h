#pragma once
#include "Entity.h"


class Character : public Entity {
    public:
        Character(const Vector& size, const Vector& pos, const Vector& speed,
        float hp, float currentHp, float atkRate, float movSpeed, SpriteAnimation* spriteAnimation);

        float getHp() const { return this->hp; }
        float getAtkRate() const { return this->atkRate; }
        float getMovSpeed() const { return this->movSpeed; }
        float getCurrentHp() const { return this->currentHp; }
        
        void setHp(float hp) { this->hp = hp; }
        void setAtkRate(float atkRate) { this->atkRate = atkRate; }
        void setMovSpeed(float movSpeed) { this->movSpeed = movSpeed; }
        void setCurrentHp(float currentHp) { this->currentHp = currentHp; }

    protected:
        float hp;
        float currentHp;
        float atkRate;
        float movSpeed;
};
