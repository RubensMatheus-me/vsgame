#include "TileManager.h"
#include "TextureManager.h"
#include "Vector.h" 
#include "Game.h"
#include "CameraManager.h"

TileManager::TileManager() {}

bool  TileManager::loadMap(const std::string& tileMapPath, const std::string& tilePropertiesPath, SDL_Renderer* renderer) {
    using json = nlohmann::json;

    std::ifstream mapFile(tileMapPath);
    std::ifstream tilesFile(tilePropertiesPath);

    if(!mapFile || !tilesFile) return false;

    json mapJson, tilesJson;
    mapFile >> mapJson;
    tilesFile >> tilesJson;

    mapWidth = mapJson["width"];
    mapHeight = mapJson["height"];
    tileWidth = mapJson["tilewidth"];
    tileHeight = mapJson["tileheight"];


    for (auto& [key, value] : tilesJson["tiles"].items()) {
        int id = std::stoi(key);

        std::string imageFile = value["image"].get<std::string>();
        std::string imagePath = "assets/sprites/tiles/" + imageFile;

        std::cout << "Tentando carregar: " << imagePath << std::endl;

        std::string textureName = "tile_" + key;

        TextureManager::loadTexture(imagePath.c_str(), textureName);

        SDL_Texture* texture = TextureManager::getTexture(textureName);
        if (!texture) continue;

        tileMap[id] = Tile {
            texture,
            value["walkable"].get<bool>(),
            value["terrainType"].get<std::string>()
        };
    }

    tileData = mapJson["layers"][0]["data"].get<std::vector<int>>();

    return true;
}

void TileManager::renderMap(SDL_Renderer* renderer, const Rect& playerCollider) {
    Vector cameraOffSet = CameraManager::getCameraManager()->getOffSet();

    for (int row = 0; row < mapHeight; ++row) {
        for (int col = 0; col < mapWidth; ++col) {
            int index = row * mapWidth + col;
            int tileId = tileData[index];

            if (tileId == 0 || tileMap.find(tileId) == tileMap.end()) continue;

            float x = static_cast<float>(col * tileWidth);
            float y = static_cast<float>(row * tileHeight);
            if(x+100 < cameraOffSet.x || x > cameraOffSet.x+CameraManager::getCameraManager()->getScreenWidth()) {
                continue; 
            }
            if(y+100 < cameraOffSet.y || y > cameraOffSet.y+CameraManager::getCameraManager()->getScreenHeight()) {
                continue;
            }
            x = x - cameraOffSet.x;
            y = y - cameraOffSet.y;

            Rect tileRect({x, y}, {static_cast<float>(tileWidth), static_cast<float>(tileHeight)});

            if (!tileMap[tileId].walkable && playerCollider.intersects(tileRect)) {
                std::cout << "Colidiu com o tile (" << col << ", " << row << ") do tipo: " 
                          << tileMap[tileId].terrainType << std::endl;
            }
            
            SDL_Rect dest = {
                static_cast<int>(x),
                static_cast<int>(y),
                tileWidth,
                tileHeight
            };

            SDL_Rect src = {0, 0, tileWidth, tileHeight};

            TextureManager::draw(tileMap[tileId].image, src, dest);

            if (!tileMap[tileId].walkable && Game::getDebugMode()) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &dest);
            }
        }
    }
}
