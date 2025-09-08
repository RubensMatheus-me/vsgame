#pragma once
#include "ILifeTime.h"

class AnimationLifeTime : public ILifetime {
public:
    AnimationLifeTime();

    void advance(float dt) override;
    bool alive(Attack& hb) override;
    void reset() override;
};