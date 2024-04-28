#include <nlohmann/json.hpp>
#include "Level.hpp"
#include "Constants.hpp"

void InitLevel(Map& map)
{
    map.mapTexture.loadFromFile(RESOURCES_PATH + "Assets/Map/Map.png");
    map.mapSprite.setTexture(map.mapTexture);
}

void DrawMap(Map& map, sf::RenderWindow& window)
{
    window.draw(map.mapSprite);
}

Level CreateLevel(const LevelDescriptor& levelDescriptor, sf::RenderWindow& window)
{
    Level level;

    for (int i = 0; i < levelDescriptor.levelSymbols.size(); ++i)
    {
        level.tiles.push_back({});
        for (int j = 0; j < levelDescriptor.levelSymbols[i].size(); ++j)
        {
            Tile tile;

            if (levelDescriptor.levelSymbols[i][j] == 'W')
            {
                tile.textureType = TileTextureType::Wall;
                tile.collisionType = TileCollisionType::Collision;
            }

            else if (levelDescriptor.levelSymbols[i][j] == 'S')
            {
                tile.textureType = TileTextureType::Empty;
                tile.collisionType = TileCollisionType::NoCollision;
            }

            level.tiles[i].push_back(tile);
        }
    }

    return level;
}

std::vector<std::vector<char>> DeserializeLevel()
{
    std::ifstream i(RESOURCES_PATH + "Assets/Map/Map.json");
    nlohmann::json j;
    i >> j;

    return j;
}