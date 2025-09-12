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
                       size_t poolSize = 50, size_t maxPopups = 10, size_t maxPerEnemy = 1)
        : renderer(renderer), fontPath(fontPath), fontSize(fontSize),
          MAX_POPUPS(maxPopups), MAX_PER_ENEMY(maxPerEnemy)
    {
        pool.resize(poolSize);
        for (auto &popup : pool)
            popup = std::make_unique<DamagePopup>();
    }

    void addPopup(const std::string &text, const Vector &pos, SDL_Color color, int enemyId = -1)
    {
        if (countActive() >= MAX_POPUPS)
        {
            removeOldest();
        }

        if (enemyId != -1 && countActiveByEnemy(enemyId) >= MAX_PER_ENEMY)
            return;

        for (auto &popup : pool)
        {
            if (!popup->isAlive())
            {
                popup->init(text, pos, color, renderer, fontPath, fontSize, enemyId);
                active.push_back(popup.get());
                lastPopup = popup.get();
                return;
            }
        }

        pool[0]->init(text, pos, color, renderer, fontPath, fontSize, enemyId);
        active.push_back(pool[0].get());
        lastPopup = pool[0].get();
    }

    void addGroupedPopup(int damage, const Vector &pos, SDL_Color color, int enemyId = -1)
    {
        if (!lastPopup || lastPopup->getEnemyId() != enemyId || !lastPopup->isAlive())
        {
            addPopup(std::to_string(damage), pos, color, enemyId);
        }
        else
        {
            lastPopup->appendDamage(damage, renderer, fontPath, fontSize);
        }
    }

    void update(float dt)
    {
        for (auto &popup : pool)
            popup->update(dt);

        active.erase(std::remove_if(active.begin(), active.end(),
                                    [](DamagePopup *p)
                                    { return !p->isAlive(); }),
                     active.end());
    }

    void render(const Vector &cameraOffset)
    {
        for (auto &popup : active)
            popup->render(renderer, cameraOffset);
    }

private:
    SDL_Renderer *renderer;
    const char *fontPath;
    int fontSize;

    std::vector<std::unique_ptr<DamagePopup>> pool;
    std::deque<DamagePopup *> active;
    DamagePopup *lastPopup = nullptr;

    size_t MAX_POPUPS;
    size_t MAX_PER_ENEMY;

    size_t countActive() const
    {
        return active.size();
    }

    size_t countActiveByEnemy(int enemyId) const
    {
        return std::count_if(active.begin(), active.end(),
                             [enemyId](DamagePopup *p)
                             { return p->getEnemyId() == enemyId; });
    }

    void removeOldest()
    {
        if (!active.empty())
            active.pop_front();
    }
};
