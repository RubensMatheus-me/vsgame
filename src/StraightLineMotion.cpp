#include "StraightLineMotion.h"
#include "Attack.h"

StraightLineMotion::StraightLineMotion(Vector direction, float speed)
    : dir(direction), speed(speed) 
{
    dir.normalize();
}

Vector StraightLineMotion::computeDelta(const Attack&, float dt) {
    return dir * speed * dt;
}