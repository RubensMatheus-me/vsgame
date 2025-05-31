#include "Character.h"

Character::Character(const Vector& size, const Vector& pos, const Vector& speed, 
                     float hp, float currentHp, float atkRate, float movSpeed, SpriteAnimation* spriteAnimation)
    : Entity(size, pos, speed, spriteAnimation), hp(hp), currentHp(currentHp), atkRate(atkRate), movSpeed(movSpeed) {}
