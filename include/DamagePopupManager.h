#pragma once
#include <vector>
#include <deque>
#include <memory>
#include <algorithm>
#include "DamagePopup.h"

class DamagePopupManager
{
public:
    DamagePopupManager(SDL_Renderer *renderer, const char *fontPath, int fontSize,
                       size_t poolSize = 50, size_t maxPopups = 10, size_t maxPerEnemy = 1);

    void addPopup(const std::string &text, const Vector &pos, SDL_Color color, int enemyId = -1);
    void addGroupedPopup(int damage, const Vector &pos, SDL_Color color, int enemyId = -1);
    void update(float dt);
    void render(const Vector &cameraOffset);

private:
    SDL_Renderer *renderer;
    const char *fontPath;
    int fontSize;

    std::vector<std::unique_ptr<DamagePopup>> pool;
    std::deque<DamagePopup *> active;
    DamagePopup *lastPopup;

    size_t MAX_POPUPS;
    size_t MAX_PER_ENEMY;

    size_t countActive() const;
    size_t countActiveByEnemy(int enemyId) const;
    void removeOldest();
};
