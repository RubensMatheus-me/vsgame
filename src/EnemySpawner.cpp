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

bool EnemySpawner::loadAllEnemiesFromFolder(const std::string &folderPath)
{
    std::cout << "loadAllEnemiesFromFolder" << std::endl;
    for (const auto &file : fs::directory_iterator(folderPath))
    {
        std::cout << folderPath << std::endl;
        if (file.path().extension() == ".json")
        {
            std::ifstream in(file.path());
            if (!in.is_open())
                continue;
            nlohmann::json config;
            in >> config;
            std::string id = config["id"];
            int weight = config["spawnWeight"];

            enemyTypes[id] = {config, weight};
            for (int i = 0; i < weight; ++i)
            {
                weightedEnemyPool.push_back(id);
            }
        }
    }
    return !enemyTypes.empty();
}

void EnemySpawner::update(float currentTime, Player *player, std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if (enemies.size() >= maxEnemies)
        return;

    if (currentTime - lastSpawnTime >= static_cast<float>(spawnIntervalMs))
    {
        spawnEnemy(player, enemies);
        lastSpawnTime = currentTime;
    }
}

void EnemySpawner::spawnEnemy(Player *player, std::vector<std::unique_ptr<Enemy>> &enemies)
{
    std::string chosenId = weightedEnemyPool[rand() % weightedEnemyPool.size()];
    const nlohmann::json &enemyConfig = enemyTypes[chosenId].config;

    CameraManager *camera = CameraManager::getCameraManager();
    Vector cameraOffset = camera->getOffSet();

    const int margin = 100;
    int spawnDistance = margin + (rand() % margin);
    int side = rand() % 4;

    float x = 0, y = 0;
    switch (side)
    {
    case 0:
        x = windowWidth + cameraOffset.x + spawnDistance;
        y = cameraOffset.y + (rand() % windowHeight);
        break;
    case 1:
        x = cameraOffset.x + (rand() % windowWidth);
        y = windowHeight + cameraOffset.y + spawnDistance;
        break;
    case 2:
        x = cameraOffset.x - spawnDistance;
        y = cameraOffset.y + (rand() % windowHeight);
        break;
    case 3:
        x = cameraOffset.x + (rand() % windowWidth);
        y = cameraOffset.y - spawnDistance;
        break;
    }

    auto anim = std::make_unique<SpriteAnimation>();
    int frameSize = enemyConfig["size"];
    int numFrames = 4;

    if (enemyConfig.contains("frames"))
    {
        numFrames = enemyConfig["frames"].size();
    }

    anim->addAnimation("idle", enemyConfig["sprite"], 0, 0,
                       frameSize, frameSize, numFrames, true);
    anim->play("idle");

    auto enemy = std::make_unique<Enemy>(
        Vector(frameSize, frameSize),
        nullptr,
        std::move(anim),
        Vector(x, y),
        Vector(enemyConfig["speed"], enemyConfig["speed"]),
        enemyConfig["hp"],
        enemyConfig["hp"],
        enemyConfig["attackRate"],
        enemyConfig["moveSpeed"],
        enemyConfig["xpDrop"],
        enemyConfig["spawnWeight"],
        enemyConfig["baseAtk"]);

    enemy->setTarget(player);
    enemies.push_back(std::move(enemy));
}
