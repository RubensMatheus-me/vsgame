#include "CollisionManager.h"
#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "GraphicalElement.h"

bool CollisionManager::checkCollision(const Rect& a, const Rect& b) {
    return a.intersects(b);
}

void CollisionManager::handlePlayerCollisions(Player* player, std::vector<std::unique_ptr<Enemy>> &enemies) {
    Rect playerRect = player->getCollider();
    
    for(size_t i = 0; i < enemies.size();i++) {
        Enemy* enemy = enemies[i].get(); 
        Rect enemyRect = enemy->getCollider();

        if(playerRect.intersects(enemyRect)) {
            if (player->getDamageCooldown() <= 0.0f) {
                player->setDamageCooldown(player->getInvunerabilityTime());
                player->setCurrentHp(player->getCurrentHp()-enemy->getBaseAtk());
				
                if (Game::getDebugMode()) std::cout << "Dano ao jogador.\n";
            } else {
                if (Game::getDebugMode()) std::cout << "Jogador invulnerável.\n";
            }
        }
    }
}

void CollisionManager::handleProjectileCollisions(Player* player, std::vector<std::unique_ptr<Enemy>> &enemies, std::vector<std::unique_ptr<Projectile>> &projectiles) {
    for (size_t i = 0; i < projectiles.size(); ++i) {
        Projectile* projectile = projectiles[i].get();
        Rect projectileRect = projectile->getCollider();
        for (size_t j = 0; j < enemies.size(); ++j) {
            Enemy* enemy = enemies[j].get();
            Rect enemyRect = enemy->getCollider();

            if(projectileRect.intersects(enemyRect)) {
                projectile->setAlive(false);

				Vector direction = enemy->getPosition() - projectile->getPosition();

				float forceKnockback = 15.5f;
				enemy->applyKnockback(direction, forceKnockback);

				if(enemy->getCurrentHp() <= 0.0f) {
					enemy->setAlive(false);
					player->setXp(player->getXp()+enemy->getXpDrop());
				}else {
					enemy->setCurrentHp(enemy->getCurrentHp() - projectile->getDamage());
				}
                
                if (Game::getDebugMode()) std::cout << "Inimigo atingido por projétil!\n";
            }
        }

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