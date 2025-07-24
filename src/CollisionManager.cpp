#include "CollisionManager.h"
#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "GraphicalElement.h"
#include "AudioManager.h"

bool CollisionManager::checkCollision(const Rect &a, const Rect &b)
{
    return a.intersects(b);
}

void CollisionManager::handlePlayerCollisions(Player *player, std::vector<std::unique_ptr<Enemy>> &enemies)
{
    Rect playerRect = player->getCollider();

    for (size_t i = 0; i < enemies.size(); i++)
    {
        Enemy *enemy = enemies[i].get();
        Rect enemyRect = enemy->getCollider();

        if (playerRect.intersects(enemyRect))
        {
            if (player->getDamageCooldown() <= 0.0f)
            {
                AudioManager::getInstance().playSound("playerHit");
                player->setDamageCooldown(player->getInvunerabilityTime());
                player->setCurrentHp(player->getCurrentHp() - enemy->getBaseAtk());

                if (Game::getDebugMode())
                    std::cout << "Dano ao jogador.\n";
            }
            else
            {
                if (Game::getDebugMode())
                    std::cout << "Jogador invulnerável.\n";
            }
        }
    }
}

void CollisionManager::handleProjectileCollisions(Player *player, std::vector<std::unique_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Projectile>> &projectiles)
{
    for (size_t i = 0; i < projectiles.size(); ++i)
    {
        Projectile *projectile = projectiles[i].get();
        Rect projectileRect = projectile->getCollider();
        for (size_t j = 0; j < enemies.size(); ++j)
        {
            Enemy *enemy = enemies[j].get();
            Rect enemyRect = enemy->getCollider();

            if (projectileRect.intersects(enemyRect))
            {
                projectile->setAlive(false);
                enemy->setAlive(false);
                player->setXp(player->getXp() + enemy->getXpDrop());

                if (Game::getDebugMode())
                    std::cout << "Inimigo atingido por projétil!\n";
            }
        }
    }
}

void CollisionManager::handleCollisionMap(Player *player, TileManager &tileManager, int mapWidth, int mapHeight)
{
    float playerX = player->getPosition().x;
    float playerY = player->getPosition().y;
    float playerSizeX = player->getSize().x;
    float playerSizeY = player->getSize().y;

    int tileWidth = tileManager.getTileWidth();
    int tileHeight = tileManager.getTileHeight();

    int startCol = std::max(0, static_cast<int>(playerX / tileWidth));
    int endCol = std::min(mapWidth - 1, static_cast<int>((playerX + playerSizeX) / tileWidth));
    int startRow = std::max(0, static_cast<int>(playerY / tileHeight));
    int endRow = std::min(mapHeight - 1, static_cast<int>((playerY + playerSizeY) / tileHeight));

    for (int row = startRow; row <= endRow; ++row) {
    for (int col = startCol; col <= endCol; ++col) {
        if (row >= 0 && row < mapHeight && col >= 0 && col < mapWidth) {
            int tileId = tileManager.getTileIdAt(row, col);
            if (tileId == -1) continue;

            if (!tileManager.isTileWalkable(tileId)) {
                float tileX = col * tileWidth;
                float tileY = row * tileHeight;

                //direita
                if (playerX + playerSizeX > tileX && playerX < tileX + tileWidth &&
                    playerY + playerSizeY > tileY && playerY < tileY + tileHeight) {
                    if (playerX + playerSizeX > tileX && playerX < tileX + tileWidth) {
                        std::cout << "Colisão à direita detectada." << std::endl;
                        player->setPosition(Vector(tileX - playerSizeX, playerY));
                    }
                }

                //esquerda
                else if (playerX < tileX + tileWidth && playerX + playerSizeX > tileX) {
                    if (playerY + playerSizeY > tileY && playerY < tileY + tileHeight) {
                        player->setPosition(Vector(tileX + tileWidth, playerY));
                    }
                }

                //baixo
                if (playerY + playerSizeY > tileY && playerY < tileY + tileHeight &&
                    playerX + playerSizeX > tileX && playerX < tileX + tileWidth) {
                    std::cout << "Colisão para baixo detectada." << std::endl;
                    player->setPosition(Vector(playerX, tileY - playerSizeY));
                }

                //cima
                else if (playerY < tileY + tileHeight && playerY + playerSizeY > tileY) {
                    if (playerX + playerSizeX > tileX && playerX < tileX + tileWidth) {
                        player->setPosition(Vector(playerX, tileY + tileHeight)); 
                    }
                }
            }
        }
    }
}

	// bordas do mapa
	if (playerX + playerSizeX > mapWidth * tileWidth) {
		player->setPosition(Vector(mapWidth * tileWidth - playerSizeX, playerY)); 
	}

	if (playerY + playerSizeY > mapHeight * tileHeight) {
		player->setPosition(Vector(playerX, mapHeight * tileHeight - playerSizeY)); 
	}

	if (playerX < 0) {
		player->setPosition(Vector(0, playerY)); 
	}

	if (playerY < 0) {
		player->setPosition(Vector(playerX, 0));
	}
}

/*
void CollisionManager::debugDrawColliders(SDL_Renderer* renderer, const std::vector<GraphicalElement*>& elements, const Vector& cameraOffset) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (auto& element : elements) {
        Rect collider = element->getCollider();

        SDL_Rect drawRect = {
            static_cast<int>(collider.x - cameraOffset.x),
            static_cast<int>(collider.y - cameraOffset.y),
            static_cast<int>(collider.w),
            static_cast<int>(collider.h)
        };

        SDL_RenderDrawRect(renderer, &drawRect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Reset cor
}
*/