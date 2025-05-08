#pragma once

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "TileManager.h"

class CollisionManager {
	
    public:
        static bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

        static void handleCollisions(const std::vector<GraphicalElement*> &elements);

		static void handleCollisions(TileManager* tileManager, Player* player, const Vector& cameraOffSet);

        void debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*> &elements, const Vector& cameraOffset);
	private:
		Player* player;
};