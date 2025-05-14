#pragma once
#include "GraphicalElement.h"
#include <string>

class Item : public GraphicalElement {
    public:
        Item(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description);

        std::string getDescription() const { return this->description; }
        void setDescription(const std::string& description) { this->description = description; }

    
    private:
        std::string description;
};