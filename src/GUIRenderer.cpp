#include "GUIRenderer.h"
#include "Player.h"
#include "CameraManager.h"

void GUIRenderer::renderXpBar(SDL_Renderer* renderer, Player* player) {
    float currentXp = player->getXp();
    float maxXp = player->getXpNextLevel();

    const int barWidth = 150;
    const int barHeight = 10;
    const int x = 10; 
    const int y = 45;

    float progress = std::min(currentXp / maxXp, 1.0f);
    int filledWidth = static_cast<int>(barWidth * progress);

    SDL_Color outlineColor = {255, 255, 255, 255};        
    SDL_Color fillColor = {0, 191, 255, 255};              
    SDL_Color backgroundColor = {25, 25, 112, 255};       

    SDL_Rect outlineRect = {x - 1, y - 1, barWidth + 2, barHeight + 2};
    SDL_Rect backgroundRect = {x, y, barWidth, barHeight};
    SDL_Rect filledRect = {x, y, filledWidth, barHeight};

    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &outlineRect);

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &backgroundRect);

    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &filledRect);
}

void GUIRenderer::renderPlayerHpBar(SDL_Renderer* renderer, Player* player) {
    float currentHp = player->getCurrentHp();
    float maxHp = player->getHp();

    float progress = std::max(0.0f, std::min(currentHp / maxHp, 1.0f));

    const int barWidth = 50;
    const int barHeight = 6;

    Vector playerPos = player->getPosition();
    Vector playerSize = player->getSize();
    Vector cameraOffset = CameraManager::getCameraManager()->getOffSet();

    int x = static_cast<int>(playerPos.x + (playerSize.x - barWidth) / 2) - cameraOffset.x;
    int y = static_cast<int>(playerPos.y + playerSize.y + 4) - cameraOffset.y;  
    int filledWidth = static_cast<int>(barWidth * progress);

    SDL_Color outlineColor = {255, 255, 255, 255};   
    SDL_Color fillColor = {255, 0, 0, 255};          
    SDL_Color backgroundColor = {139, 0, 0, 255};   

    SDL_Rect outlineRect = {x - 1, y - 1, barWidth + 2, barHeight + 2};
    SDL_Rect backgroundRect = {x, y, barWidth, barHeight};
    SDL_Rect filledRect = {x, y, filledWidth, barHeight};

    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &outlineRect);

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &backgroundRect);

    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &filledRect);
}

void GUIRenderer::renderItems(SDL_Renderer* renderer, Player* player) {
	std::vector<std::unique_ptr<Upgrade>>& upgrades = player->getUpgrades();
	Vector cameraOffset = CameraManager::getCameraManager()->getOffSet();
	for (int i = 0; i < upgrades.size(); i++) {
		float x = 5.0f + (i * 32.0f) + (5.0f*i);
		float y = 60.0f;    
		upgrades[i]->render(renderer, Vector(cameraOffset.x+x, cameraOffset.y+y));
	}
}