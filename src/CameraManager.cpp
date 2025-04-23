#include "CameraManager.h"

CameraManager::CameraManager(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), offSet(0.0f, 0.0f) {}

void CameraManager::follow(const Vector& targetPosition) {
    offSet.x = targetPosition.x - screenWidth / 2;
    offSet.y = targetPosition.y - screenHeight / 2;
    
}