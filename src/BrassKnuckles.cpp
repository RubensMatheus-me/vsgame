#include "BrassKnuckles.h"
#include "MeleeAttack.h"

BrassKnuckles::BrassKnuckles(
    const Vector& size,
    SpriteAnimation* spriteAnimation,
    const std::string& description,
    float flatDamage,
    float flatAtkSpeed,
    float damageMultiplier,
    float atkSpeedMultiplier,
    int level,
    SpriteAnimation* punchAnimation,
    float attackDuration
)
    : MeleeWeapon(size, spriteAnimation, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level),
      punchAnimation(punchAnimation),
      attackDuration(attackDuration)
{}

void BrassKnuckles::attack(const Vector& position, const Vector& direction, Entity* owner) {
    auto animation = std::make_unique<SpriteAnimation>(); 
    std::vector<SDL_Rect> leftFrames;
    std::vector<SDL_Rect> rightFrames;

    SDL_Rect rightFrame1 = {0, 0, 32, 32};
    SDL_Rect rightFrame2 = {0, 0, 80, 32};
    SDL_Rect rightFrame3 = {0, 0, 144, 32};
    
    rightFrames.push_back(rightFrame1);
    rightFrames.push_back(rightFrame2);
    rightFrames.push_back(rightFrame3);

    animation->addAnimation("right", "brassKnuckles", rightFrames, false);
    // if(direction[0] > 0) {
    //     animation->play("right");
    // } else {
    //     animation->play("left");
    // }
    animation->play("right");
    std::cout << direction << std::endl;

    Vector newPosition;
    if(direction[0] == 1) {
        newPosition = position + Vector(30.0f, 0.0f);
    } else {
        newPosition = position - Vector(5.0f, 0.0f);
    }

    auto p = std::make_unique<MeleeAttack>(
        Vector(144.0f, 32.0f),
        newPosition,
        direction,
        50.0f,
        std::move(animation),  
        owner
    );

    getMeleeAttacks().push_back(std::move(p));
}

void BrassKnuckles::render(SDL_Renderer* renderer) {
    if (getSprite()) {
        getSprite()->render(renderer, 1, 1);
    }
}

void BrassKnuckles::update(float deltaTime) {
    if (getSprite()) {
        getSprite()->update(deltaTime);
    }
}
