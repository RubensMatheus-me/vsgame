#include "Character.h"

Character::Character(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed, 
                     float hp, float atkRate, float movSpeed)
    : Entity(width, height, image, pos, speed), hp(hp), atkRate(atkRate), movSpeed(movSpeed) {}
