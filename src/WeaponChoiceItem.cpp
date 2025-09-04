#include "WeaponChoiceItem.h"

WeaponChoiceItem::WeaponChoiceItem(WeaponChoice* weapon)
    : weapon(weapon) {}

void WeaponChoiceItem::render(SDL_Renderer* renderer, const Vector& pos) {
    if (weapon->sprite) {
        weapon->sprite->render(renderer, 1, 1);
    }
}

std::string WeaponChoiceItem::getDescription() const {
    return weapon->description;
}

bool WeaponChoiceItem::isWeapon() const {
    return true;
}

WeaponChoice* WeaponChoiceItem::getWeapon() const {
    return weapon;
}
