#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

class FontCache
{
public:
    static SDL_Texture *getTextTexture(SDL_Renderer *renderer,
                                       const std::string &text,
                                       const std::string &fontPath,
                                       SDL_Color color,
                                       int fontSize)
    {
        std::string key = text + "_" + std::to_string(color.r) + "_" +
                          std::to_string(color.g) + "_" +
                          std::to_string(color.b) + "_" +
                          std::to_string(fontSize);

        if (cache.find(key) != cache.end())
        {
            return cache[key];
        }

        TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font)
            return nullptr;

        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
        TTF_CloseFont(font);

        cache[key] = texture;
        return texture;
    }

    static void clear()
    {
        for (auto &[k, tex] : cache)
            SDL_DestroyTexture(tex);
        cache.clear();
    }

private:
    static inline std::unordered_map<std::string, SDL_Texture *> cache;
};
