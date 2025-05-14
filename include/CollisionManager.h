#pragma once

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Rect.h"
#include <vector>

class CollisionManager {
    public:
        static bool checkCollision(const Rect& a, const Rect& b);

        static void handleCollisions(const std::vector<GraphicalElement*> &elements);

        void debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*> &elements, const Vector& cameraOffset);

};