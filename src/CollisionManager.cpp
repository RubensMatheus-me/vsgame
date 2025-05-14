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
            std::cout << "Rect A: (" << rectA.x << ", " << rectA.y << ", " << rectA.w << ", " << rectA.h << ")\n";
            std::cout << "Rect B: (" << rectB.x << ", " << rectB.y << ", " << rectB.w << ", " << rectB.h << ")\n";

            if (rectA.intersects(rectB)) {
                std::cout << "Colisão detectada!" << std::endl;
                Player* player = dynamic_cast<Player*>(entityA);
                Entity* other = entityB;

                if (!player) {
                    player = dynamic_cast<Player*>(entityB);
                    other = entityA;
                }

                if (player) {
                    if (player->getDamageCooldown() <= 0.0f) {
                        if (Game::getDebugMode()) {
                            std::cout << "Dano causado ao jogador.\n";
                        }
                        player->setDamageCooldown(player->getInvunerabilityTime());
                    } else {
                        if (Game::getDebugMode()) {
                            std::cout << "Colidiu, mas jogador está invulnerável.\n";
                        }
                    }
                }

                if (Game::getDebugMode()) {
                    std::cout << "Colidiu com o inimigo.\n";
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