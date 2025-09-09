#pragma once
#include "IMotion.h"

class StraightLineMotion : public IMotion {
public:
    StraightLineMotion(Vector direction, float speed);

    Vector computeDelta(const Attack& h, float dt) override;

private:
    Vector dir;
    float speed;
};