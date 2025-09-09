#pragma once
#include <string>
#include "SpriteAnimation.h"

struct WeaponChoice {
    int id;
    std::string name;
    std::string description;
    SpriteAnimation* sprite;
};
