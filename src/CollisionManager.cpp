#include "CollisionManager.h"
#include "Game.h"
#include <iostream>
#include "Player.h"
#include "GraphicalElement.h"
#include "TileManager.h"


bool CollisionManager::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

void CollisionManager::handleCollisions(TileManager* tileManager, Player* player, const Vector& cameraOffSet) {

	std::map<int, TileManager::Tile> tileMap = tileManager->getTileMap();
	const SDL_Rect playerRect = player->getCollider();

	for (int row = 0; row < tileManager->getMapHeight(); ++row) {
        for (int col = 0; col < tileManager->getMapWidth(); ++col) {
            int index = row * tileManager->getMapWidth() + col;
            int tileId = tileManager->getTileData()[index];

            if (tileId == 0 || tileMap.find(tileId) == tileMap.end()) continue;

            int x = col * tileManager->getTileWidth() - cameraOffSet.x;
            int y = row * tileManager->getTileHeight() - cameraOffSet.y;

            SDL_Rect tileRect = {x, y, tileManager->getTileWidth(), tileManager->getTileHeight()};

			
            if(!tileMap[tileId].walkable && SDL_HasIntersection(&playerRect, &tileRect)) {
                std::cout << "Colidiu com o tile (" << col << ", " << row << ") do tipo: " << tileMap[tileId].terrainType << std::endl;
				float tileX =  static_cast<float>(tileRect.x);
				float maxX = std::max(tileX, player->getPosition().x);
				float minX = std::min(tileX, player->getPosition().x);

				float tileY =  static_cast<float>(tileRect.y);
				float maxY = std::max(tileY, player->getPosition().y);
				float minY = std::min(tileY, player->getPosition().y);
				
				float deltaX = maxX-minX; 
				float deltaY = maxY-minY;

				player->setPosition({deltaX, deltaY});

            }
        }
    }
}

void CollisionManager::handleCollisions(const std::vector<GraphicalElement*> &elements) {
	for (size_t j = 1; j < elements.size(); ++j) {
		SDL_Rect rectA = elements[0]->getCollider();
		SDL_Rect rectB = elements[j]->getCollider();
		
		if (SDL_HasIntersection(&rectA, &rectB)) {

			Player* player = dynamic_cast<Player*>(elements[0]);
			GraphicalElement* others = elements[j];

			if(!player) {
				player = dynamic_cast<Player*>(elements[j]);
				others = elements[j];
			}

			if(player) {
				if(player->getDamageCooldown() <= 0.0f) {
					if(Game::getDebugMode()) {
						std::cout << "dano" << std::endl;
					}
					player->setDamageCooldown(player->getInvunerabilityTime());
				} else {
					if(Game::getDebugMode()) {
					}
				}
			}
			
			if(Game::getDebugMode() == true) {
				std::cout << "Colidiu com o inimigo" << std::endl;
			}
		} 
	}
}




void CollisionManager::debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*> &elements ,const Vector& cameraOffset) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for(auto& element : elements) {
        SDL_Rect collider = element->getCollider();

        SDL_Rect drawRect = {
            collider.x - static_cast<int>(cameraOffset.x),
            collider.y - static_cast<int>(cameraOffset.y),
            collider.w,
            collider.h,
        };
        SDL_RenderDrawRect(renderer, &drawRect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}