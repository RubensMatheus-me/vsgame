#pragma once
#include "IMotion.h"
#include "Vector.h"
#include "Entity.h"

class OrbitMotion : public IMotion {
public:
    OrbitMotion(const Entity* center, float radius, float angularSpeed, float initialAngle = 0.0f);

    Vector computeDelta(const Attack& h, float dt) override;

private:
    const Entity* center;
    float radius;
    float angularSpeed;
    float angle;
};
