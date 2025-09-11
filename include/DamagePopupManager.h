#pragma once
#include <vector>
#include <deque>
#include <memory>
#include "DamagePopup.h"

class DamagePopupManager
{
public:
    DamagePopupManager(const char *fontPath, int fontSize,
                       size_t maxPopups = 5, size_t maxPerEnemy = 1)
        : fontPath(fontPath), fontSize(fontSize),
          MAX_POPUPS(maxPopups), MAX_PER_ENEMY(maxPerEnemy) {}

    void addPopup(const std::string &text, const Vector &pos, SDL_Color color, int enemyId = -1)
    {
        if (active.size() >= MAX_POPUPS)
        {
            active.pop_front();
        }

        if (enemyId != -1 && countActiveByEnemy(enemyId) >= MAX_PER_ENEMY)
        {
            return;
        }

        active.push_back(std::make_unique<DamagePopup>(text, pos, color, enemyId));
    }

    void update(float dt)
    {
        for (auto &popup : active)
            popup->update(dt);

        auto it = std::remove_if(active.begin(), active.end(),
                                 [](const std::unique_ptr<DamagePopup> &p)
                                 {
                                     return !p->isAlive();
                                 });
        active.erase(it, active.end());
    }

    void render(SDL_Renderer *renderer, const Vector &cameraOffset)
    {
        size_t rendered = 0;
        for (auto &popup : active)
        {
            if (rendered >= MAX_RENDER_PER_FRAME)
                break;
            popup->render(renderer, cameraOffset);
            rendered++;
        }
    }

    void addGroupedPopup(int damage, const Vector &pos, SDL_Color color, int enemyId = -1)
    {
        if (!lastPopup || lastPopup->getEnemyId() != enemyId || !lastPopup->isAlive())
        {
            addPopup(std::to_string(damage), pos, color, enemyId);
            lastPopup = active.back().get();
        }
        else
        {
            lastPopup->appendDamage(damage);
        }
    }

private:
    const char *fontPath;
    int fontSize;
    std::deque<std::unique_ptr<DamagePopup>> active;
    size_t MAX_POPUPS;
    size_t MAX_PER_ENEMY;
    size_t MAX_RENDER_PER_FRAME = 5;

    DamagePopup *lastPopup = nullptr;

    size_t countActiveByEnemy(int enemyId)
    {
        return std::count_if(active.begin(), active.end(),
                             [enemyId](const std::unique_ptr<DamagePopup> &p)
                             {
                                 return p->getEnemyId() == enemyId;
                             });
    }
};
