#pragma once
#include "GraphicalElement.h"
#include <string>

class Item : public GraphicalElement {
    public:
        Item(float width, float height, SDL_Texture *image, const std::string& description);

        std::string getDescription() const { return this->description; }
        void setDescription(const std::string& description) { this->description = description; }

    
    private:
        std::string description;
};