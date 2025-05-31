#include "CameraManager.h"

CameraManager::CameraManager(){}

CameraManager* CameraManager::instance = nullptr;

void  CameraManager::init(int x, int y) {
    screenWidth = x;
    screenHeight = y;
    offSet = {0.0f,0.0f};
}

void CameraManager::follow(const Vector& targetPosition) {
    offSet.x = targetPosition.x - screenWidth / 2;
    offSet.y = targetPosition.y - screenHeight / 2;
}

CameraManager* CameraManager::getCameraManager() {
    if (instance == nullptr) {
        instance = new CameraManager(); 
    }
    return instance;
}