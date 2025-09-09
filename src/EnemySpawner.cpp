#include "EnemySpawner.h"
#include "Enemy.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "Vector.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <random>
#include "CameraManager.h"

namespace fs = std::filesystem;

EnemySpawner::EnemySpawner(int maxEnemies, int spawnIntervalSeconds, int width, int height)
    : maxEnemies(maxEnemies), spawnIntervalSeconds(spawnIntervalSeconds), windowWidth(width), windowHeight(height), spawnTimer(spawnIntervalSeconds), totalSpawned(0),
    rng(std::random_device{}()) {}


void EnemySpawner::update(float deltaTime, Player *player, std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if (enemies.size() >= maxEnemies)
        return;

    spawnTimer.update(deltaTime);

    if (spawnTimer.hasElapsed())
    {
        spawnEnemy(player, enemies);
        spawnTimer.reset();
    }
}

void EnemySpawner::spawnEnemy(Player *player, std::vector<std::unique_ptr<Enemy>> &enemies)
{

    if (weightedEnemyPool.empty())
    {
        std::cerr << "EnemySpawner::spawnEnemy é chamada, mas weightedEnemyPool é vazia!" << std::endl;
        return;
    }

    std::uniform_int_distribution<int> dist(0, static_cast<int>(weightedEnemyPool.size()) - 1);
    

    std::string chosenId = weightedEnemyPool[dist(rng)];
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
        enemyConfig["baseAtk"],
		enemyConfig["hp"]
    );
    enemy->setCurrentHp(enemyConfig["hp"]);
    enemy->setTarget(player);
    totalSpawned++;
    enemies.push_back(std::move(enemy));
}


void EnemySpawner::clearPool() {
    weightedEnemyPool.clear();
    enemyTypes.clear();
    totalSpawned = 0;
}

void EnemySpawner::addEnemyType(const std::string& id, int weight) {
    std::ifstream in ("assets/data/enemies/" + id + ".json");

    if(!in.is_open()) {
        std::cerr << "Erro: não consegui abrir o json de: " << id << std::endl;
        return;
    }

    nlohmann::json config;
    in >> config;

    enemyTypes[id] = {config, weight};

    for(int i = 0; i < weight; ++i) {
        weightedEnemyPool.push_back(id);
    }
    std::cerr << "addEnemyType: " << id << " weight=" << weight << std::endl;
}

int EnemySpawner::getWeightedPoolSize() const {
    return static_cast<int>(weightedEnemyPool.size());
}

int EnemySpawner::getTotalSpawned() const {
    return totalSpawned;
}