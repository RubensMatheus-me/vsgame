#pragma once
#include "enums/GameState.h"

class GameStateManager
{
public:
    static GameStateManager &getInstance()
    {
        static GameStateManager instance;
        return instance;
    }

    void setState(GameState state) { currentState = state; }
    GameState getState() const { return currentState; }

    bool isInGame() const { return currentState == GameState::InGame; }
    bool isInUpgrade() const { return currentState == GameState::InUpgrade; }
    bool isInLose() const { return currentState == GameState::InLose; }

private:
    GameState currentState = GameState::InGame;

    GameStateManager() = default;
    GameStateManager(const GameStateManager &) = delete;
    void operator=(const GameStateManager &) = delete;
};
