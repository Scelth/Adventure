#pragma once
#include "Constants.hpp"
#include "Sound.hpp"

enum class PlayerLastDirection
{
    Left,
    Right
};

struct Player
{
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::FloatRect playerRect;
    sf::Vector2f playerVelocity;
    sf::FloatRect playerAttackArea;

    PlayerLastDirection playerLastDirection = PlayerLastDirection::Right;

    float playerSpeed = PLAYER_SPEED;
    float CurrentFrame = 0;
    float playerHealth = 5.f;
};

void InitPlayer(Player& player);

void UpdatePlayer(Player& player,
    Sound& sound, 
    const float time);

float PlayerAttack(Player& player, 
    sf::FloatRect& enemyRect,
    float enemyHealth,
    Sound& sound);

void PlayerDirection(Player& player);

bool IsPlayerAlive(const Player& player, Sound& sound);