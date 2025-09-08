#include "TimedLifeTime.h"

TimedLifetime::TimedLifetime(float duration)
    : elapsed(0.0f), duration(duration){}

void TimedLifetime::advance(float dt) {
    elapsed += dt;
}

bool TimedLifetime::alive(Attack&) {
    return elapsed < duration;
}

void TimedLifetime::reset() {
    elapsed = 0.0f;
}