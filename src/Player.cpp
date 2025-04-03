#include "Player.h"

Player::Player(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float movSpeed, float xp, int level, float atkSpeed)
    : Character(width, height, image, pos, speed, hp, atkRate, movSpeed), xp(xp), level(level), atkSpeed(atkSpeed) {}