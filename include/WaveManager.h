#pragma once

#include "EnemySpawner.h"
#include "Player.h"
#include "Timer.h"
#include <nlohmann/json.hpp>
#include <fstream>


struct EnemyWave {
    int waveNumber;
    float spawnRate;
    int maxEnemies;
    std::vector<std::pair<std::string, int>> enemies;
};

class WaveManager {
    public:
        WaveManager(const std::string& filePath, int screenWidth, int screenHeight);

        void update(float deltaTime, Player* player, std::vector<std::unique_ptr<Enemy>>& enemies);
		void cleanUp();

    private:
        std::vector<EnemyWave> waves;
        int currentWaveIndex = -1;

        std::unique_ptr<EnemySpawner> spawner;
        Timer waveTimer;

        int screenHeight;
        int screenWidth;

        void loadWaves(const std::string& filePath);
        void startWave(int index);
};