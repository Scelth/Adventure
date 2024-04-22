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
	Tile tile;
	LevelDescriptor levelDescriptor;
	Sound sound;
	UI ui;

	int playerPauseChoice;
	bool gamePaused = false;
};

void CallMainMenu(sf::RenderWindow& window);

void StartGame(sf::RenderWindow& window);

void HandleWindowEvents(sf::RenderWindow& window, 
	GameLogic& gameLogic);

void InitGame(GameLogic& gameLogic, 
	sf::Texture& tileSetTexture, 
	sf::Sprite& tileSprite);

void UpdateGame(GameLogic& gameLogic,
	const float clockDeltaSeconds,
	const float time,
	sf::RenderWindow& window);

void DrawGame(sf::RenderWindow& window,
	GameLogic& gameLogic,
	const sf::Sprite& tileSprite);

void GameCamera(GameLogic& gameLogic, 
	sf::RenderWindow& window);