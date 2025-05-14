#include "Character.h"

Character::Character(const Vector& size, const Vector& pos, const Vector& speed, 
                     float hp, float atkRate, float movSpeed, SpriteAnimation* spriteAnimation)
    : Entity(size, pos, speed, spriteAnimation), hp(hp), atkRate(atkRate), movSpeed(movSpeed) {}
