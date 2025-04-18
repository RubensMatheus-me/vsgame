#include "TextureManager.h" 
#include "Game.h"
#include "SDL_ttf.h"


SDL_Renderer* TextureManager::renderer = nullptr;
std::map<std::string, SDL_Texture*> TextureManager::textures;

void TextureManager::init(SDL_Renderer* ren) {
    renderer = ren;
}
void TextureManager::loadTexture(const char* filename, std::string textureName){
    if (textures[textureName] != NULL) {
        std::cout << "Já existe essa textura, tente outra!" << std::endl;
        return;
    };

    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(filename);

    if (tempSurface == NULL) {
        std::cout << "Erro ao carregar imagem, IMG_ERROR: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (texture == NULL) {
        std::cout << "Não foi possivel criar uma texture de surface, SDL_ERROR: " << SDL_GetError() <<std::endl;
        return;
    }

    SDL_FreeSurface(tempSurface);
    textures[textureName] = texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect) {
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

SDL_Texture *TextureManager::getTexture(std::string textureName) {
    if (textures[textureName] == NULL) {
        std::cout << "Não foi possivel achar a textura: " << textureName << std::endl;
        return nullptr;
    }
    return textures[textureName];
}

SDL_Texture* TextureManager::renderText(const std::string text, const std::string fontPath, SDL_Color color, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if(!font) {
        std::cout << "Erro ao carregar fonte:" << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    
    return texture;
}

void TextureManager::cleanTexture() {
    for (auto& t : textures) {
        SDL_DestroyTexture(t.second);
        t.second = nullptr;
    }
	textures.clear();
	std::cout << "texturas limpas e map vazio" << std::endl;
}