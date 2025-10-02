#pragma once
#include "enums/GameState.h"

class GameStateManager
{
public:
    static GameStateManager &getInstance();

    void setState(GameState state);
    GameState getState() const;

    bool isInGame() const;
    bool isInUpgrade() const;
    bool isInLose() const;

private:
    GameState currentState = GameState::InGame;

    GameStateManager();
    GameStateManager(const GameStateManager &) = delete;
    void operator=(const GameStateManager &) = delete;
};
