#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include <memory>

class TextDisplayManager {
public:
    TextDisplayManager(SDL_Renderer* renderer, const std::string& fontPath);
    ~TextDisplayManager();

    void updateText(const std::string& key, const std::string& newText, int fontSize, SDL_Color color);
    SDL_Texture* getTexture(const std::string& key) const;
    void renderText(const std::string& key, int x, int y);

    void clear();

private:
    struct TextData {
        std::string currentText;
        SDL_Texture* texture = nullptr;
        int width = 0;
        int height = 0;
    };

    SDL_Renderer* renderer;
    std::string fontPath;
    std::map<std::string, TextData> texts;
};
