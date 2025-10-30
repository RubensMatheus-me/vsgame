#include "DamagePopupManager.h"
#include <string>

DamagePopupManager::DamagePopupManager(SDL_Renderer *renderer, const char *fontPath, int fontSize,
                                       size_t poolSize, size_t maxPopups, size_t maxPerEnemy)
    : renderer(renderer), fontPath(fontPath), fontSize(fontSize),
      MAX_POPUPS(maxPopups), MAX_PER_ENEMY(maxPerEnemy), lastPopup(nullptr)
{
    pool.resize(poolSize);
    for (auto &popup : pool)
        popup = std::make_unique<DamagePopup>();
}

void DamagePopupManager::addPopup(const std::string &text, const Vector &pos, SDL_Color color, int enemyId)
{
    if (countActive() >= MAX_POPUPS)
        removeOldest();

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

void DamagePopupManager::addGroupedPopup(int damage, const Vector &pos, SDL_Color color, int enemyId)
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

void DamagePopupManager::update(float dt)
{
    for (auto &popup : pool)
        popup->update(dt);

    active.erase(std::remove_if(active.begin(), active.end(),
                                [](DamagePopup *p) { return !p->isAlive(); }),
                 active.end());
}

void DamagePopupManager::render(const Vector &cameraOffset)
{
    for (auto &popup : active)
        popup->render(renderer, cameraOffset);
}

size_t DamagePopupManager::countActive() const
{
    return active.size();
}

size_t DamagePopupManager::countActiveByEnemy(int enemyId) const
{
    return std::count_if(active.begin(), active.end(),
                         [enemyId](DamagePopup *p) { return p->getEnemyId() == enemyId; });
}

void DamagePopupManager::removeOldest()
{
    if (!active.empty())
        active.pop_front();
}
