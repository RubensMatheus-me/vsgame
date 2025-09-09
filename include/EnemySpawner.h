#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"

class EnemySpawner {
public:
    EnemySpawner(int maxEnemies, int spawnIntervalMs, int windowWidth, int windowHeight);

    void update(float deltaTime, Player* player, std::vector<std::unique_ptr<Enemy>>& enemies);
    bool loadAllEnemiesFromFolder(const std::string& folderPath);

    void clearPool();
    void addEnemyType(const std::string& id, int weight);

private:
    struct EnemyData {
        nlohmann::json config;
        int spawnWeight;
    };

    std::unordered_map<std::string, EnemyData> enemyTypes;
    std::vector<std::string> weightedEnemyPool;

    int maxEnemies;
    int spawnIntervalSeconds;
    int windowWidth, windowHeight;
    Timer spawnTimer;

    void spawnEnemy(Player* player, std::vector<std::unique_ptr<Enemy>>& enemies);
};