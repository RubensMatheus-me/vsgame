#include "Enemy.h"


Enemy::Enemy(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
             float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight)
    : Character(width, height, image, pos, speed, hp, atkRate, movSpeed),
      xpDrop(xpDrop), spawnWeight(spawnWeight) {}
