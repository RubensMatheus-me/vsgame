#pragma once

#include "Vector.h"
namespace Config {


	//Player base stats
	inline const Vector PLAYER_SIZE(32, 32);
    inline const Vector PLAYER_SPEED(0.5f, 0.5f);
    inline constexpr float PLAYER_HP = 100.0f;
    inline constexpr float PLAYER_ATTACK_RATE = 1.0f;
    inline constexpr float PLAYER_MOV_SPEED = 100.0f;
    inline constexpr float PLAYER_INITIAL_XP = 0.0f;
    inline constexpr int PLAYER_INITIAL_LEVEL = 1;
    inline constexpr float PLAYER_ATTACK_SPEED = 1.5f;
    inline constexpr bool PLAYER_IS_MOVING = false;
    inline const Vector PLAYER_INITIAL_DIRECTION(0, 0);
    inline constexpr float PLAYER_DAMAGE_COOLDOWN = 0.0f;
    inline constexpr float PLAYER_INVULNERABILITY_TIME = 1.0f;
    inline constexpr float INITIAL_NEXT_LEVEL_EXPERIENCE = 100.0f;
    inline constexpr float NEXT_LEVEL_EXPERIENCE_RATE = 2.0f;

    // Enemy base stats
    inline const Vector ENEMY_SIZE(32, 32);
    inline const Vector ENEMY_SPEED(0, 0);
    inline constexpr float ENEMY_HP = 10.0f;
    inline constexpr float ENEMY_ATTACK_RATE = 1.0f;
    inline constexpr float ENEMY_MOV_SPEED = 50.0f;
    inline constexpr float ENEMY_XP_DROP = 5.0f;
    inline constexpr int ENEMY_SPAWN_WEIGHT = 1;
    inline constexpr int ENEMY_BASE_ATK = 10.0f;
    //Enemy spawner
    inline constexpr int MAX_ENEMIES = 100;
    inline constexpr int SPAWN_INTERVAL = 1;
}
