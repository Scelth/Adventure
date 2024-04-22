#pragma once
#include <SFML/Graphics.hpp>
#include <string>

const std::string RESOURCES_PATH("Resources/");
const std::string GAME_NAME("Adventure");
const int SCREEN_WIDTH(1280);
const int SCREEN_HEIGTH(720);
const float PLAYER_SPEED(300.f);
const float ENEMY_SPEED(200.f);
const float PLAYER_ATTACK_RADIUS(50.f);
const int ENEMIES_COUNT(15);

const float ENEMIES_SPAWN_POSITIONS[ENEMIES_COUNT][2] = {
	{ 60, 2755 },
	{ 535, 2925 },
	{ 1200, 2885 },
	{ 1510, 1275 },
	{ 1705, 2655 },
	{ 1865, 1645 },
	{ 2140, 2670 },
	{ 2350, 2145 },
	{ 2450, 1680 },
	{ 2720, 1675 },
	{ 2835, 2225 },
	{ 2945, 1675 },
	{ 3240, 1675 },
	{ 3240, 2000 },
	{ 3240, 2225}
};

const sf::Vector2f CHARACTER_SIZE(192.f, 192.f);
const sf::Vector2f CHARACTER_DRAW_SCALE(1.2f, 1.2f);
const sf::Vector2f PLAYER_SPAWN(750.f, 20.f);
const sf::Vector2i TEXTURE_TILE_SIZE(5.f, 5.f);
const sf::Vector2f DRAW_SCALE(10.f, 10.f);
const sf::Vector2f TILE_SIZE(TEXTURE_TILE_SIZE.x * DRAW_SCALE.x, TEXTURE_TILE_SIZE.y * DRAW_SCALE.y);