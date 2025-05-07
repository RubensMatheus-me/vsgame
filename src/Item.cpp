#include "Item.h"

Item::Item(float width, float height, SpriteAnimation* spriteAnimation, const std::string& description)
    : GraphicalElement(width, height, spriteAnimation), description(description) {}