#include "CollisionManager.h"
#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "GraphicalElement.h"

bool CollisionManager::checkCollision(const Rect& a, const Rect& b) {
    return a.intersects(b);
}
void CollisionManager::handleCollisions(const std::vector<GraphicalElement*>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        for (size_t j = i + 1; j < elements.size(); ++j) {
            Entity* entityA = dynamic_cast<Entity*>(elements[i]);
            Entity* entityB = dynamic_cast<Entity*>(elements[j]);

            if (!entityA || !entityB) continue;

            Rect rectA = entityA->getCollider();
            Rect rectB = entityB->getCollider();

            if (rectA.intersects(rectB)) {
                Player* player = dynamic_cast<Player*>(entityA);
                Entity* other = entityB;

                if (!player) {
                    player = dynamic_cast<Player*>(entityB);
                    other = entityA;
                }

                Projectile* projectile = dynamic_cast<Projectile*>(entityA);
                Entity* target = entityB;
                if (!projectile) {
                    projectile = dynamic_cast<Projectile*>(entityB);
                    target = entityA;
                }

                if (projectile && projectile->getOwner() == target) {
                    continue; 
                }

                Enemy* enemy = dynamic_cast<Enemy*>(entityA);
                if (!enemy) enemy = dynamic_cast<Enemy*>(entityB);
                if (projectile && enemy) {
                    projectile->setAlive(false);
                    enemy->setAlive(false);
                    if (Game::getDebugMode()) std::cout << "Inimigo atingido por projétil!\n";
                    continue;
                }

                if (player) {
                    if (player->getDamageCooldown() <= 0.0f) {
                        player->setDamageCooldown(player->getInvunerabilityTime());
                        if (Game::getDebugMode()) std::cout << "Dano ao jogador.\n";
                    } else {
                        if (Game::getDebugMode()) std::cout << "Jogador invulnerável.\n";
                    }
                }
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