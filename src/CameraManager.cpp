#include "CameraManager.h"

CameraManager::CameraManager(){}

CameraManager* CameraManager::instance = nullptr;

void CameraManager::init(int windowWidth, int windowHeight, int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
    screenWidth = windowWidth;
    screenHeight = windowHeight;
	this->mapWidth = mapWidth * tileWidth;
	this->mapHeight = mapHeight * tileHeight;
    offSet = {0.0f,0.0f};
}

void CameraManager::follow(const Vector& targetPosition) {
    offSet.x = targetPosition.x - screenWidth / 2;
    offSet.y = targetPosition.y - screenHeight / 2;

	if (offSet.x < 0) {
		offSet.x = 0;
	} else if (offSet.x + screenWidth > mapWidth) {
		offSet.x = mapWidth - screenWidth;
	}

	if (offSet.y < 0) {
		offSet.y = 0;
	} else if (offSet.y + screenHeight > mapHeight) {
		offSet.y = mapHeight - screenHeight;
	}
}

CameraManager* CameraManager::getCameraManager() {
    if (instance == nullptr) {
        instance = new CameraManager(); 
    }
    return instance;
}