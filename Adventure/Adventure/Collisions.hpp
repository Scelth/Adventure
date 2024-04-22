#pragma once
#include "Level.hpp"

enum class EOrientaion
{
    Horizontal,
    Vertical
};

struct CollisionResult
{
    bool bIsCollided = false;
    sf::Vector2f newPosition;
};

void CheckCollision(sf::FloatRect& objectRect,
    sf::Vector2f& objectVelocity,
    Level& level,
    const float clockDeltaSeconds);

CollisionResult HandleCollision(const sf::FloatRect& objectRect,
    const sf::Vector2f& objectVelocity,
    const Level& level,
    EOrientaion orientation);

bool HandlePlayerEnemyCollision(sf::FloatRect& playerRect,
    sf::FloatRect& enemyRect);