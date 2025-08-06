#pragma once

#include "Vector.h"
#include <vector>
#include "GraphicalElement.h"

class CameraManager{
    public:
        static CameraManager* instance;
        CameraManager();

        void follow(const Vector& targetPosition);
        void addElement(GraphicalElement* element);
        void renderAll(SDL_Renderer* renderer);
        void clearElements();
        static CameraManager* getCameraManager();
        void init(int windowWidth, int windowHeight, int mapWidth, int mapHeight, int tileWidth, int tileHeight);

        Vector getOffSet() const {return this->offSet;}

        int getScreenWidth() { return this->screenWidth; }
        int getScreenHeight() { return this->screenHeight; }

        CameraManager(CameraManager &other) = delete;
        void operator=(const CameraManager &) = delete;
        
    private:
        int screenWidth;
        int screenHeight;
		int mapWidth;
		int mapHeight;
        Vector offSet;
        std::vector<GraphicalElement*> elements;
};