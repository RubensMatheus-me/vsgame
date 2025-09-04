#pragma once
#include "ChoiceItem.h"
#include "WeaponChoice.h"

class WeaponChoiceItem : public ChoiceItem {
public:
    explicit WeaponChoiceItem(WeaponChoice* weapon);

    void render(SDL_Renderer* renderer, const Vector& pos) override;
    std::string getDescription() const override;
    bool isWeapon() const override;

    WeaponChoice* getWeapon() const;

private:
    WeaponChoice* weapon;
};
