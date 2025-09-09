#include "WaveManager.h"
#include <iostream>

WaveManager::WaveManager(const std::string& filePath, int screenWidth, int screenHeight) : waveTimer(60.0f), screenWidth(screenWidth), screenHeight(screenHeight) {
    loadWaves(filePath);
}

void WaveManager::loadWaves(const std::string& filePath) {
    std::ifstream in(filePath);
    nlohmann::json data;
    in >> data;

    for (auto& w : data) {
        EnemyWave wave;
        wave.waveNumber = w["wave"];
        wave.spawnRate = w["spawnRate"];
        wave.maxEnemies = w["maxEnemies"];

        for (auto& e : w["enemies"]) {
            wave.enemies.push_back({e["enemy"], e["spawnWeight"]});
        }
        waves.push_back(wave);
    }
}

void WaveManager::startWave(int index) {
    if (index >= (int)waves.size()) return;

    auto& wave = waves[index];
    currentWaveIndex = index;

    //float spawnIntervalSeconds = 1.0f / wave.spawnRate;
    //spawner = std::make_unique<EnemySpawner>(wave.maxEnemies, spawnIntervalSeconds, screenWidth, screenHeight);

    spawner = std::make_unique<EnemySpawner>(wave.maxEnemies, wave.spawnRate, screenWidth, screenHeight);

    spawner->clearPool();
    for (auto& [id, weight] : wave.enemies) {
        spawner->addEnemyType(id, weight);
    }

    waveTimer.reset();

    std::cout << "Wave " << wave.waveNumber << " iniciada!" << std::endl;
}

void WaveManager::update(float deltaTime, Player* player, std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (currentWaveIndex == -1) {
        startWave(0);
    }

    if (spawner) {
        spawner->update(deltaTime, player, enemies);
    }

    waveTimer.update(deltaTime);

    if (waveTimer.hasElapsed() && enemies.empty()) {
        if(currentWaveIndex + 1 < (int)waves.size()) {
            startWave(currentWaveIndex + 1);
        } else {
            std::cout << "All waves completed!" << std::endl;
        }
    }
}