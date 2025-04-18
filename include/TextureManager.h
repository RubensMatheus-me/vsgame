#pragma once

#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>


class TextureManager {
    public:
        static void init(SDL_Renderer* ren);
        static void loadTexture(const char* filename, std::string textureName);
        static SDL_Texture* getTexture(std::string textureName);

        static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
        static void cleanTexture();

        static SDL_Texture* renderText(std::string text, std::string fontPath, SDL_Color color, int fontSize);

    private:
        static SDL_Renderer *renderer;
        static std::map<std::string, SDL_Texture*> textures; 
};