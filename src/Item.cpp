#include "Item.h"

Item::Item(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description)
    : GraphicalElement(size, spriteAnimation), description(description) {}
    
SpriteAnimation* Item::getSpriteAnimation() const {
    return spriteAnimation;
}