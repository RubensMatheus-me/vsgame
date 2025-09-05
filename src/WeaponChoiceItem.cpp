#include "WeaponChoiceItem.h"
#include "TextureManager.h"

WeaponChoiceItem::WeaponChoiceItem(WeaponChoice* weapon)
    : weapon(weapon) {}

void WeaponChoiceItem::render(SDL_Renderer* renderer, const Vector& pos) {
    if (weapon->sprite) {
        weapon->sprite->render(renderer, 1, 1);
        const int ICON_SIZE = 29;
        SDL_Rect destRect = {
            static_cast<int>(pos.x),
            static_cast<int>(pos.y),
            ICON_SIZE,
            ICON_SIZE};
        SDL_Rect srcRect =  weapon->sprite->getCurrentFrameRect();

        SDL_Texture *texture = TextureManager::getTexture( weapon->sprite->getCurrentTextureName());
        SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
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
