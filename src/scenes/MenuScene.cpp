#include "scenes/MenuScene.h"
#include "GameStateManager.h"
#include "enums/GameState.h"

MenuScene::MenuScene(Game* game) : game(game) {}

MenuScene::~MenuScene() {
    cleanUp(); 
}

void MenuScene::init() {
    font = TTF_OpenFont("assets/fonts/dogica.ttf", 24);
    if (!font) {
        std::cerr << "Erro ao carregar a fonte: " << TTF_GetError() << std::endl;
    }
}

void MenuScene::handleInput(SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        game->clean();
    } 
    else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            GameStateManager::getInstance().setState(GameState::InGame);
        } 
        else if (event.key.keysym.sym == SDLK_ESCAPE) {
            game->clean();
        }
    }
}

void MenuScene::renderText(const std::string& text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->getRenderer(), surface);

    int textW = surface->w;
    int textH = surface->h;
    SDL_Rect renderQuad = {x, y, textW, textH};

    SDL_RenderCopy(game->getRenderer(), texture, nullptr, &renderQuad);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void MenuScene::render() {
    SDL_RenderClear(game->getRenderer());

    renderText("Pressione Enter para Iniciar", game->getWidth() / 4, game->getHeight() / 2);

    SDL_RenderPresent(game->getRenderer());
}

void MenuScene::cleanUp() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void MenuScene::update(float dt) {
    // Atualizações podem ser feitas aqui se necessário
}
