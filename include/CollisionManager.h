#pragma once

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Rect.h"
#include "TileManager.h"
#include <vector>

class CollisionManager {
    public:
        static bool checkCollision(const Rect& a, const Rect& b);

        static void handlePlayerCollisions(Player* player, std::vector<std::unique_ptr<Enemy>> &enemies);
        static void handleProjectileCollisions(Player* player, std::vector<std::unique_ptr<Enemy>>  &enemies, std::vector<std::unique_ptr<Projectile>> &projectiles);
        
        static void handleCollisions(const std::vector<GraphicalElement*> &elements);

		static void handleCollisionMap(Player* player, TileManager &tileManager, int mapWidth, int mapHeight);

        void debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*> &elements, const Vector& cameraOffset);

};