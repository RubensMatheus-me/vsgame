#include "OrbitMotion.h"
#include "Attack.h"
#include <cmath>

OrbitMotion::OrbitMotion(const Entity* center, float radius, float angularSpeed, float initialAngle)
    : center(center), radius(radius), angularSpeed(angularSpeed), angle(initialAngle) {}

Vector OrbitMotion::computeDelta(const Attack& h, float dt) {
    angle += angularSpeed * dt;

    Vector targetPos = center->getPosition() + Vector(std::cos(angle) * radius, std::sin(angle) * radius);

    Vector delta = targetPos - h.getPosition();
    return delta;
}
