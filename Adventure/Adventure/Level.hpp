#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
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
    sf::Texture tileSetTexture;
    std::map<TileTextureType, sf::IntRect> tileTextureTypeToTextureRect;
};

void InitLevel(sf::Texture& tileSetTexture, sf::Sprite& tileSprite);
Level CreateLevel(const LevelDescriptor& levelDescriptor, sf::RenderWindow& window);
std::vector<std::vector<char>> DeserializeLevel();