#pragma once
#include "ChoiceItem.h"
#include "Upgrade.h"

class UpgradeChoiceItem : public ChoiceItem {
public:
    explicit UpgradeChoiceItem(Upgrade* upgrade);

    void render(SDL_Renderer* renderer, const Vector& pos) override;
    std::string getDescription() const override;
    bool isWeapon() const override;

    Upgrade* getUpgrade() const;

private:
    Upgrade* upgrade;
};
