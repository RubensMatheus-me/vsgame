#include "Item.h"

Item::Item(float width, float height, SDL_Texture *image, const std::string& description)
    : GraphicalElement(width, height, image), description(description) {}