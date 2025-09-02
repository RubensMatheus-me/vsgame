#pragma once
#include "IMotion.h"
#include <cmath>

class WaveMotion : public IMotion {
public:
    WaveMotion(Vector direction, float speed, float frequency, float amplitude);
    Vector computeDelta(const Attack& h, float dt) override;

private:
    Vector dir;
    float speed;
    float freq;
    float amplitude;
    float time;
};