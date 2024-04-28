#pragma once
#include <SFML/Graphics.hpp>

struct UI
{
	static const int maxMenuOptions = 2;
	static const int maxPauseMenuOptions = 3;

	int menuSelected;
	int pauseSelected;
	int deadSelected;

	sf::Texture menuTexture;
	sf::Sprite menuSprite;

	sf::Texture pauseMenuTexture;
	sf::Sprite pauseMenuSprite;

	sf::Font uiTextFont;
	sf::Font healthTextFont;

	sf::Text healthText;
	sf::Text mainMenuText[maxMenuOptions];
	sf::Text deadMenuText[maxMenuOptions];
	sf::Text pauseMenuText[maxPauseMenuOptions];
};

void InitUI(UI& ui);

void DrawUIText(UI& ui,
	sf::RenderWindow& window);

void MainMenuDraw(UI& mainMenu,
	sf::RenderWindow& window);

void PauseMenuDraw(UI& ui,
	sf::RenderWindow& window);

void DeadMenuDraw(UI& ui,
	sf::RenderWindow& window);

void MainMenuMove(UI& mainMenu,
	const sf::Event& event);

void PauseMenuMove(UI& ui,
	const sf::Event& event);

void DeadMenuMove(UI& ui,
	const sf::Event& event);