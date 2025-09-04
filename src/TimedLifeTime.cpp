#include "TimedLifeTime.h"

TimedLifetime::TimedLifetime(float duration)
    : elapsed(0.0f), duration(duration){}

void TimedLifetime::advance(float dt) {
    elapsed += dt;
}

bool TimedLifetime::alive(const Attack&) {
    return elapsed < duration;
}