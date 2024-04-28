#pragma once
#include "Constants.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Level.hpp"
#include "Sound.hpp"
#include "UI.hpp"

struct GameLogic
{
	Player player;
	Enemy enemies[ENEMIES_COUNT];
	Level level;
	Map map;
	Tile tile;
	LevelDescriptor levelDescriptor;
	Sound sound;
	UI ui;

	bool gamePaused = false;
};

void CallMainMenu(sf::RenderWindow& window);

void StartGame(sf::RenderWindow& window);

void HandleWindowEvents(sf::RenderWindow& window,
	GameLogic& gameLogic);

void InitGame(GameLogic& gameLogic);

void UpdateGame(GameLogic& gameLogic,
	const float clockDeltaSeconds,
	const float frameTime,
	sf::RenderWindow& window);

void DrawGame(sf::RenderWindow& window,
	GameLogic& gameLogic);

void GameCamera(GameLogic& gameLogic,
	sf::RenderWindow& window);