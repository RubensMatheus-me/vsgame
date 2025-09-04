#include "UpgradeChoiceItem.h"

UpgradeChoiceItem::UpgradeChoiceItem(Upgrade* upgrade)
    : upgrade(upgrade) {}

void UpgradeChoiceItem::render(SDL_Renderer* renderer, const Vector& pos) {
    upgrade->render(renderer, pos);
}

std::string UpgradeChoiceItem::getDescription() const {
    return upgrade->getDescription();
}

bool UpgradeChoiceItem::isWeapon() const {
    return false;
}

Upgrade* UpgradeChoiceItem::getUpgrade() const {
    return upgrade;
}
