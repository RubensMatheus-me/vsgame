#pragma once

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class CollisionManager {
    public:
        static bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

        static void handleCollisions(const std::vector<GraphicalElement*> &elements);

        void debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*> &elements, const Vector& cameraOffset);

};