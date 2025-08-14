#include "EnemySpawner.h"
#include "Enemy.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "Vector.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include "CameraManager.h"

namespace fs = std::filesystem;

EnemySpawner::EnemySpawner(int maxEnemies, int spawnIntervalMs, int width, int height)
    : maxEnemies(maxEnemies), spawnIntervalMs(spawnIntervalMs), windowWidth(width), windowHeight(height) {}

bool EnemySpawner::loadAllEnemiesFromFolder(const std::string &folderPath) {
    std::cout << "loadAllEnemiesFromFolder"<< std::endl;
    for (const auto& file : fs::directory_iterator(folderPath)) {
        std::cout <<  folderPath << std::endl;
        if (file.path().extension() == ".json") {
            std::ifstream in(file.path());
            if (!in.is_open()) continue;
            nlohmann::json config;
            in >> config;
            std::string id = config["id"];
            int weight = config["spawnWeight"];

            enemyTypes[id] = { config, weight };
            for (int i = 0; i < weight; ++i) {
                weightedEnemyPool.push_back(id);
            }
        }
    }
    return !enemyTypes.empty();
}

void EnemySpawner::update(float currentTime, Player* player, std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (enemies.size() >= maxEnemies) return;

    if (currentTime - lastSpawnTime >= static_cast<float>(spawnIntervalMs)) {
        spawnEnemy(player, enemies);
        lastSpawnTime = currentTime;
    }
}

void EnemySpawner::spawnEnemy(Player* player, std::vector<std::unique_ptr<Enemy>>& enemies) {
    //std::string chosenId = weightedEnemyPool[static_clast<int>(rand() % weightedEnemyPool.size())];
    //nlohmann::json enemyConfig =
    std::cout << "spawnEnemy"<< std::endl;
    std::string chosenId = weightedEnemyPool[rand() % weightedEnemyPool.size()];
    const nlohmann::json enemyConfig = enemyTypes[chosenId].config;
	
	CameraManager* camera = CameraManager::getCameraManager();
	Vector cameraOffset = camera->getOffSet();
	int offsetX = static_cast<int>(cameraOffset.x);
	int offsetY = static_cast<int>(cameraOffset.y);

    int side = rand() % 4;
    float x = 0, y = 0;
	int margin = 100;

    switch(side) {
        case 0:
			x = windowWidth + offsetX + (margin % rand());
			y = windowHeight + offsetY + (margin % rand());
			break;
        case 1:
			x = windowWidth + offsetX + (margin % rand());
			y = offsetY - (margin % rand());
			break;
        case 2:
			x = offsetX - (margin % rand());
			y = windowHeight + offsetY + (margin % rand());
			break;
        case 3:
			x = offsetX - (margin % rand());
			y = offsetY - (margin % rand());
			break;
    }

    auto anim = std::make_unique<SpriteAnimation>();
    anim->addAnimation("idle", enemyConfig["sprite"], 0, 0, enemyConfig["width"], enemyConfig["height"], 1, true);

    anim->play("idle");
    Vector size = {enemyConfig["size"], enemyConfig["size"]};
    Vector speed = {enemyConfig["speed"], enemyConfig["speed"]};
    auto enemy = std::make_unique<Enemy>(
        size,
        nullptr,
        std::move(anim),
        Vector(x, y),
        speed,
        enemyConfig["hp"],
        enemyConfig["hp"],
        enemyConfig["attackRate"],
        enemyConfig["moveSpeed"],
        enemyConfig["xpDrop"],
        enemyConfig["spawnWeight"],
        enemyConfig["baseAtk"],
		enemyConfig["hp"]
    );

    enemy->setTarget(player);

    Enemy* rawEnemyPtr = enemy.get();
    enemies.emplace_back(std::move(enemy));
}
