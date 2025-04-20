#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include <SDL2/SDL.h>


class TileManager {
    public:
        struct Tile {
            SDL_Texture* image;
            bool walkable;
            std::string terrainType;
        }; 
    
    TileManager();

    bool loadMap(const std::string& tileMapPath, const std::string& tilePropertiesPath, SDL_Renderer* renderer);
    void renderMap(SDL_Renderer* renderer);

    int getTileWidth() const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }

    private:
        int mapWidth, mapHeight;
        int tileWidth, tileHeight;
        std::map<int, Tile> tileMap;
        std::vector<int> tileData;

};