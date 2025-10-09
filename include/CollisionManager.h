#pragma once

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Rect.h"
#include "TileManager.h"
#include "DamagePopupManager.h"
#include <vector>

class CollisionManager {
    public:
		void setDamagePopupManager(DamagePopupManager* popupMgr) {this->damagePopupManager = popupMgr;}
        static bool checkCollision(const Rect& a, const Rect& b);

        void handlePlayerCollisions(Player* player, std::vector<std::unique_ptr<Enemy>> &enemies);
		void handleProjectileCollisions(Player *player, std::vector<std::unique_ptr<Enemy>> &enemies);

		void NewFunction(std::unique_ptr<Attack> &attack, Enemy *enemy);

		void handleEnemyCollisions(std::vector<std::unique_ptr<Enemy>> &enemies, Player* player);

		void handleCollisionMap(Player* player, TileManager &tileManager, int mapWidth, int mapHeight);

        void debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*> &elements, const Vector& cameraOffset);
	private:
	    DamagePopupManager* damagePopupManager = nullptr;
};