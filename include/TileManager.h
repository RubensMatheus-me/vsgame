#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include "Vector.h"


class TileManager {
    public:
        struct Tile {
            SDL_Texture* image;
            bool walkable;
            std::string terrainType;
        }; 
    
    TileManager();

    bool loadMap(const std::string& tileMapPath, const std::string& tilePropertiesPath, SDL_Renderer* renderer);
    void renderMap(SDL_Renderer* renderer, const Vector& cameraOffSet, const SDL_Rect playerCollider);

    int getTileWidth() const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }
	std::map<int, Tile> getTileMap() const { return tileMap;}
	std::vector<int> getTileData() const {return tileData;}

	int getMapWidth() const {return mapWidth;}
	int getMapHeight() const {return mapHeight;}

    private:
        int mapWidth, mapHeight;
        int tileWidth, tileHeight;
        std::map<int, Tile> tileMap;
        std::vector<int> tileData;

};