#pragma once
#include <SFML/Graphics.hpp>

struct UI
{
	static const int maxMainMenu = 2;
	static const int maxPauseMenu = 3;

	int mainSelected;
	int pauseSelected;
	
	sf::Texture mainMenuTexture;
	sf::Sprite mainMenuSprite;

	sf::Texture pauseMenuTexture;
	sf::Sprite pauseMenuSprite;

	sf::Font uiTextFont;
	sf::Font healthTextFont;

	sf::Text healthText;
	sf::Text mainMenuText[maxMainMenu];
	sf::Text pauseMenuText[maxPauseMenu];
};

void InitMainMenu(UI& mainMenu);

void InitUI(UI& ui);

void MainMenuDraw(sf::RenderWindow& window,
	UI& mainMenu);

void PauseMenuDraw(sf::RenderWindow& window,
	UI& ui);

void MainMenuMove(UI& mainMenu, 
	const sf::Event& event);

void PauseMenuMove(UI& ui, 
	const sf::Event& event);