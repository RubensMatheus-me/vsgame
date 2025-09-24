#include "GameStateManager.h"

GameStateManager &GameStateManager::getInstance()
{
    static GameStateManager instance;
    return instance;
}

GameStateManager::GameStateManager() = default;

void GameStateManager::setState(GameState state)
{
    currentState = state;
}

GameState GameStateManager::getState() const
{
    return currentState;
}

bool GameStateManager::isInGame() const
{
    return currentState == GameState::InGame;
}

bool GameStateManager::isInUpgrade() const
{
    return currentState == GameState::InUpgrade;
}

bool GameStateManager::isInLose() const
{
    return currentState == GameState::InLose;
}
