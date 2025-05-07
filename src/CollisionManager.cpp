#include "CollisionManager.h"
#include "Game.h"
#include <iostream>
#include "Player.h"
#include "GraphicalElement.h"

bool CollisionManager::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

void CollisionManager::handleCollisions(const std::vector<GraphicalElement*> &elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        for (size_t j = i + 1; j < elements.size(); ++j) {
            SDL_Rect rectA = elements[i]->getCollider();
            SDL_Rect rectB = elements[j]->getCollider();
            
            if (SDL_HasIntersection(&rectA, &rectB)) {

                Player* player = dynamic_cast<Player*>(elements[i]);
                GraphicalElement* others = elements[j];

                if(!player) {
                    player = dynamic_cast<Player*>(elements[j]);
                    others = elements[i];
                }

                if(player) {
                    if(player->getDamageCooldown() <= 0.0f) {
                        if(Game::getDebugMode()) {
                            std::cout << "dano" << std::endl;
                        }
                        player->setDamageCooldown(player->getInvunerabilityTime());
                    } else {
                        if(Game::getDebugMode()) {
                            std::cout << "colidiu, mas ainda está invulnerável" << std::endl;
                        }
                    }
                }
                
                if(Game::getDebugMode() == true) {
                    std::cout << "Colidiu com o inimigo" << std::endl;
                }
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