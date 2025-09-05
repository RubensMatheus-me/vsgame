#pragma once
#include <string>
#include "Vector.h"
#include <SDL2/SDL.h>

class ChoiceItem {
public:
    virtual ~ChoiceItem() = default;

    virtual void render(SDL_Renderer* renderer, const Vector& pos) = 0;
    virtual std::string getDescription() const = 0;
    virtual bool isWeapon() const = 0;
};