#include "Character.h"

Character::Character(float width, float height, const Vector& pos, const Vector& speed, 
                     float hp, float atkRate, float movSpeed, SpriteAnimation* spriteAnimation)
    : Entity(width, height, pos, speed, spriteAnimation), hp(hp), atkRate(atkRate), movSpeed(movSpeed) {}
