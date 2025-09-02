#pragma once
#include "Vector.h"

class Attack;

struct IMotion {
    virtual ~IMotion() = default;
    virtual Vector computeDelta(const Attack& h, float dt) = 0;
};
