#pragma once

#include "Vector.h"
#include <vector>
#include "GraphicalElement.h"

class CameraManager{
    public:
        CameraManager(int screenWidth, int screenHeight);

        void follow(const Vector& targetPosition);
        void addElement(GraphicalElement* element);
        void renderAll(SDL_Renderer* renderer);
        void clearElements();

        Vector getOffSet() const {return this->offSet;}

    private:
        int screenWidth;
        int screenHeight;
        Vector offSet;
        std::vector<GraphicalElement*> elements;
};