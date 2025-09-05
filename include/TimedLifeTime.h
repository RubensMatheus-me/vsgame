#pragma once
#include "ILifeTime.h"

class TimedLifetime : public ILifetime {
public:
    TimedLifetime(float duration);

    void advance(float dt) override;
    bool alive(const Attack& hb) override;
    void reset() override;
    
private:
    float elapsed;
    float duration;
};