#pragma once
#include "Constants.hpp"
#include "Sound.hpp"

enum class EnemyLastDirection
{
    Left,
    Right
};

struct Enemy
{
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    sf::FloatRect enemyRect;
    sf::Vector2f enemyVelocity;

    float enemySpeed = ENEMY_SPEED;
    float CurrentFrame = 0;
    EnemyLastDirection enemyLastlDirection = EnemyLastDirection::Right;

    float enemyHealth = 3.f;
    int direction;
    float directionChangeCooldown = 3.0f;
};

void InitEnemy(Enemy& enemy);

void UpdateEnemy(Enemy& enemy,
    const float time);

float EnemyAttack(Enemy& enemy,
    sf::FloatRect& playerRect,
    float playerHealth,
    Sound& sound);

void EnemyDirection(Enemy& enemy);