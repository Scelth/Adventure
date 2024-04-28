#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "TileType.hpp"

struct Tile
{
    TileTextureType textureType;
    TileCollisionType collisionType;
};

struct Level
{
    std::vector<std::vector<Tile>> tiles;
    std::map<TileTextureType, sf::Sprite> tileTextureTypeToSprite;
};

struct LevelDescriptor
{
    std::vector<std::vector<char>> levelSymbols;
    sf::Texture levelTexture;
    std::map<TileTextureType, sf::IntRect> textureTypeToTextureRect;
};

struct Map
{
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
};

void InitLevel(Map& map);

void DrawMap(Map& map,
    sf::RenderWindow& window);

Level CreateLevel(const LevelDescriptor& levelDescriptor,
    sf::RenderWindow& window);

std::vector<std::vector<char>> DeserializeLevel();