#include "OrbitMotion.h"
#include "Attack.h"
#include <cmath>

OrbitMotion::OrbitMotion(const Entity* center, float radius, float angularSpeed, float initialAngle)
    : center(center), radius(radius), angularSpeed(angularSpeed), angle(initialAngle) {}

Vector OrbitMotion::computeDelta(const Attack& h, float dt) {
    angle += angularSpeed * dt;
    if (angle >= 360.0f) angle -= 360.0f;
    if (angle < 0.0f) angle += 360.0f;
    float rad = angle * (3.1415f / 180.0f);

    Vector targetPos = center->getPosition() + Vector(std::cos(rad) * radius,std::sin(rad) * radius);

    return targetPos - h.getPosition();
}
