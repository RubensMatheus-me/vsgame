#pragma once
#include <SDL2/SDL.h>
#include "Player.h"
#include "Vector.h"

class GUIRenderer
{
public:
    static void renderXpBar(SDL_Renderer *renderer, Player *player);
    static void renderPlayerHpBar(SDL_Renderer *renderer, Player *player);
    static void renderItems(SDL_Renderer *renderer, Player *player);
    static void renderPlayerInfo(SDL_Renderer *renderer, Player *player);
};