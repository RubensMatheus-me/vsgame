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

    // Calcula colunas e linhas do mapa que o player ocupa
    int startCol = std::max(0, static_cast<int>(playerX / tileWidth));
    int endCol = std::min(mapWidth - 1, static_cast<int>((playerX + playerSizeX) / tileWidth));
    int startRow = std::max(0, static_cast<int>(playerY / tileHeight));
    int endRow = std::min(mapHeight - 1, static_cast<int>((playerY + playerSizeY) / tileHeight));

    for (int row = startRow; row <= endRow; ++row) {
        for (int col = startCol; col <= endCol; ++col) {
            int tileId = tileManager.getTileIdAt(row, col);
            if (tileId == -1) continue;

            if (!tileManager.isTileWalkable(tileId)) {
                float tileX = col * tileWidth;
                float tileY = row * tileHeight;

                bool collisionX = playerX + playerSizeX > tileX && playerX < tileX + tileWidth;
                bool collisionY = playerY + playerSizeY > tileY && playerY < tileY + tileHeight;

				if (collisionX && collisionY) {
					float overlapX1 = (playerX + playerSizeX) - tileX;
					float overlapX2 = (tileX + tileWidth) - playerX;
					float overlapY1 = (playerY + playerSizeY) - tileY;
					float overlapY2 = (tileY + tileHeight) - playerY;

					float minOverlapX = std::min(overlapX1, overlapX2);
					float minOverlapY = std::min(overlapY1, overlapY2);

					if (minOverlapX < minOverlapY) {
						if (playerX + playerSizeX / 2 < tileX + tileWidth / 2)
							playerX = tileX - playerSizeX;
						else
							playerX = tileX + tileWidth;
					} else {
						if (playerY + playerSizeY / 2 < tileY + tileHeight / 2)
							playerY = tileY - playerSizeY;
						else
							playerY = tileY + tileHeight;
					}
				}
            }
        }
    }

    float maxX = mapWidth * tileWidth - playerSizeX;
    float maxY = mapHeight * tileHeight - playerSizeY;

    if (playerX < 0) playerX = 0;
    else if (playerX > maxX) playerX = maxX;

    if (playerY < 0) playerY = 0;
    else if (playerY > maxY) playerY = maxY;

    player->setPosition(Vector(playerX, playerY));
}
