#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

class EnemySpawner {
public:
    EnemySpawner(int maxEnemies, int spawnIntervalMs, int windowWidth, int windowHeight);

    void update(float currentTime, Player* player, std::vector<std::unique_ptr<Enemy>>& enemies);
    bool loadAllEnemiesFromFolder(const std::string& folderPath);

private:
    struct EnemyData {
        nlohmann::json config;
        int spawnWeight;
    };

    std::unordered_map<std::string, EnemyData> enemyTypes;
    std::vector<std::string> weightedEnemyPool;

    int maxEnemies;
    int spawnIntervalMs;
    int windowWidth, windowHeight;
    float lastSpawnTime = 0.0f;

    void spawnEnemy(Player* player, std::vector<std::unique_ptr<Enemy>>& enemies);
};