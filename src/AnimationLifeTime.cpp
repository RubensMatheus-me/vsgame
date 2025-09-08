#include "AnimationLifeTime.h"
#include "Attack.h"

AnimationLifeTime::AnimationLifeTime() {
}

void AnimationLifeTime::advance(float dt) {
}

bool AnimationLifeTime::alive(Attack& attack) {
    return !attack.getSprite()->animationEnded();
}

void AnimationLifeTime::reset() {
}