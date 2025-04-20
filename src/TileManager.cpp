#include "TileManager.h"
#include "TextureManager.h"

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

void TileManager::renderMap(SDL_Renderer* renderer) {
    for (int row = 0; row < mapHeight; ++row) {
        for (int col = 0; col < mapWidth; ++col) {
            int index = row * mapWidth + col;
            int tileId = tileData[index];

            if (tileId == 0 || tileMap.find(tileId) == tileMap.end()) continue;

            SDL_Rect dest = {col * tileWidth, row * tileHeight, tileWidth, tileHeight};
            SDL_Rect src = {0, 0, tileWidth, tileHeight};

            TextureManager::draw(tileMap[tileId].image, src, dest);

            std::cout << "Tile ID: " << tileId << " at (" << col << ", " << row << ")" << std::endl;
        }
    }
}