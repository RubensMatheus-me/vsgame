#include "TextDisplayManager.h"
#include <iostream>

TextDisplayManager::TextDisplayManager(SDL_Renderer* renderer, const std::string& fontPath)
    : renderer(renderer), fontPath(fontPath) {}

TextDisplayManager::~TextDisplayManager() {
    clear();
}

void TextDisplayManager::updateText(const std::string& key, const std::string& newText, int fontSize, SDL_Color color) {
    auto& textData = texts[key];

    if (textData.currentText == newText)
        return; 

    if (textData.texture) {
        SDL_DestroyTexture(textData.texture);
        textData.texture = nullptr;
    }

    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, newText.c_str(), color);
    if (!surface) {
        std::cerr << "Erro ao criar surface de texto: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Erro ao criar textura de texto: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    textData.texture = texture;
    textData.currentText = newText;
    textData.width = surface->w;
    textData.height = surface->h;

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

SDL_Texture* TextDisplayManager::getTexture(const std::string& key) const {
    auto it = texts.find(key);
    if (it != texts.end()) {
        return it->second.texture;
    }
    return nullptr;
}

void TextDisplayManager::renderText(const std::string& key, int x, int y) {
    auto it = texts.find(key);
    if (it == texts.end() || it->second.texture == nullptr) return;

    SDL_Rect destRect = { x, y, it->second.width, it->second.height };
    SDL_RenderCopy(renderer, it->second.texture, nullptr, &destRect);
}

void TextDisplayManager::clear() {
    for (auto& [key, data] : texts) {
        if (data.texture) {
            SDL_DestroyTexture(data.texture);
            data.texture = nullptr;
        }
    }
    texts.clear();
}
