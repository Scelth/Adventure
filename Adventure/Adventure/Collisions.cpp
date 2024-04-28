#include "Collisions.hpp"
#include "Constants.hpp"

void CheckCollision(sf::FloatRect& objectRect,
    sf::Vector2f& objectVelocity,
    Level& level,
    const float clockDeltaSeconds)
{
    CollisionResult collisionResult;

    {
        objectRect.left += objectVelocity.x * clockDeltaSeconds;
        collisionResult = HandleCollision(objectRect, objectVelocity, level, EOrientaion::Horizontal);
        if (collisionResult.bIsCollided)
        {
            objectRect.left = collisionResult.newPosition.x;
        }
    }

    {
        objectRect.top -= objectVelocity.y * clockDeltaSeconds;
        collisionResult = HandleCollision(objectRect, objectVelocity, level, EOrientaion::Vertical);
        if (collisionResult.bIsCollided)
        {
            objectRect.top = collisionResult.newPosition.y;
        }
    }
}

CollisionResult HandleCollision(
    const sf::FloatRect& objectRect,
    const sf::Vector2f& objectVelocity,
    const Level& level,
    EOrientaion orientation)
{
    const int xLeftTile = objectRect.left / TILE_SIZE.x;
    int xRightTile = (objectRect.left + objectRect.width - 1.f) / TILE_SIZE.x;

    const int yTopTile = objectRect.top / TILE_SIZE.y;
    int yBottomTile = (objectRect.top + objectRect.height - 1.f) / TILE_SIZE.y;

    CollisionResult result;
    result.newPosition = objectRect.getPosition();

    for (int i = yTopTile; i <= yBottomTile; ++i)
    {
        for (int j = xLeftTile; j <= xRightTile; ++j)
        {
            const Tile& tile = level.tiles[i][j];
            const sf::Vector2f tilePosition = sf::Vector2f(j * TILE_SIZE.x, i * TILE_SIZE.y);

            if (tile.collisionType == TileCollisionType::Collision)
            {
                result.bIsCollided = true;

                if (orientation == EOrientaion::Horizontal)
                {
                    if (objectVelocity.x < 0.f)
                    {
                        result.newPosition = sf::Vector2f(tilePosition.x + TILE_SIZE.x, objectRect.top);
                    }

                    else
                    {
                        result.newPosition = sf::Vector2f(tilePosition.x - objectRect.width, objectRect.top);
                    }
                }

                else
                {
                    if (objectVelocity.y < 0.f)
                    {
                        result.newPosition = sf::Vector2f(objectRect.left, tilePosition.y - objectRect.height);
                    }

                    else
                    {
                        result.newPosition = sf::Vector2f(objectRect.left, tilePosition.y + TILE_SIZE.y);
                    }
                }
            }
        }
    }

    return result;
}

bool HandlePlayerEnemyCollision(sf::FloatRect& playerRect,
    sf::FloatRect& enemyRect)
{
    if (playerRect.intersects(enemyRect))
    {
        return true;
    }

    return false;
}