#include "UI.hpp"
#include "Constants.hpp"

void InitMainMenu(UI& mainMenu)
{
	mainMenu.mainMenuTexture.loadFromFile(RESOURCES_PATH + "Assets/Menu/MainMenu.png");
	mainMenu.mainMenuSprite.setTexture(mainMenu.mainMenuTexture);

	mainMenu.uiTextFont.loadFromFile(RESOURCES_PATH + "Fonts/UI.ttf");

	mainMenu.mainMenuText[0].setFont(mainMenu.uiTextFont);
	mainMenu.mainMenuText[0].setFillColor(sf::Color::Red);
	mainMenu.mainMenuText[0].setString("Play");
	mainMenu.mainMenuText[0].setCharacterSize(50);
	mainMenu.mainMenuText[0].setPosition(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGTH / 4);

	mainMenu.mainMenuText[1].setFont(mainMenu.uiTextFont);
	mainMenu.mainMenuText[1].setFillColor(sf::Color::Black);
	mainMenu.mainMenuText[1].setString("Exit");
	mainMenu.mainMenuText[1].setCharacterSize(50);
	mainMenu.mainMenuText[1].setPosition(SCREEN_WIDTH / 2 - 50, (SCREEN_HEIGTH / 4) * 2.3);

	mainMenu.mainSelected = 0;
}

void InitUI(UI& ui)
{
	ui.pauseMenuTexture.loadFromFile(RESOURCES_PATH + "Assets/Menu/PauseMenu.png");
	ui.pauseMenuSprite.setTexture(ui.pauseMenuTexture);

	ui.uiTextFont.loadFromFile(RESOURCES_PATH + "Fonts/UI.ttf");

	ui.healthText.setFont(ui.uiTextFont);
	ui.healthText.setFillColor(sf::Color::White);

	ui.pauseMenuText[0].setFont(ui.uiTextFont);
	ui.pauseMenuText[0].setFillColor(sf::Color::Red);
	ui.pauseMenuText[0].setString("Resume");
	ui.pauseMenuText[0].setCharacterSize(50);
			 
	ui.pauseMenuText[1].setFont(ui.uiTextFont);
	ui.pauseMenuText[1].setFillColor(sf::Color::Black);
	ui.pauseMenuText[1].setString("Restart");
	ui.pauseMenuText[1].setCharacterSize(50);
			 
	ui.pauseMenuText[2].setFont(ui.uiTextFont);
	ui.pauseMenuText[2].setFillColor(sf::Color::Black);
	ui.pauseMenuText[2].setString("Exit");
	ui.pauseMenuText[2].setCharacterSize(50);

	ui.pauseSelected = 0;
}

void MainMenuDraw(sf::RenderWindow& window,
	UI& mainMenu)
{
	window.clear();

	window.draw(mainMenu.mainMenuSprite);

	for (int i = 0; i < 2; i++)
	{
		window.draw(mainMenu.mainMenuText[i]);
	}

	window.display();
}

void PauseMenuDraw(sf::RenderWindow& window,
	UI& ui)
{
	window.clear();

	window.draw(ui.pauseMenuSprite);

	for (int i = 0; i < 3; i++)
	{
		window.draw(ui.pauseMenuText[i]);
	}

	window.display();
}

void MainMenuMove(UI& mainMenu, const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Down)
	{
		if (mainMenu.mainSelected + 1 <= mainMenu.maxMainMenu)
		{
			mainMenu.mainMenuText[mainMenu.mainSelected].setFillColor(sf::Color::Black);
			mainMenu.mainSelected++;

			if (mainMenu.mainSelected == mainMenu.maxMainMenu)
			{
				mainMenu.mainSelected = 0;
			}

			mainMenu.mainMenuText[mainMenu.mainSelected].setFillColor(sf::Color::Red);
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		if (mainMenu.mainSelected - 1 >= -1)
		{
			mainMenu.mainMenuText[mainMenu.mainSelected].setFillColor(sf::Color::Black);
			mainMenu.mainSelected--;

			if (mainMenu.mainSelected == -1)
			{
				mainMenu.mainSelected = 1;
			}

			mainMenu.mainMenuText[mainMenu.mainSelected].setFillColor(sf::Color::Red);
		}
	}
}

void PauseMenuMove(UI& ui, const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Down)
	{
		if (ui.pauseSelected + 1 <= ui.maxPauseMenu)
		{
			ui.pauseMenuText[ui.pauseSelected].setFillColor(sf::Color::Black);
			ui.pauseSelected++;

			if (ui.pauseSelected == ui.maxPauseMenu)
			{
				ui.pauseSelected = 0;
			}

			ui.pauseMenuText[ui.pauseSelected].setFillColor(sf::Color::Red);
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		if (ui.pauseSelected - 1 >= -1)
		{
			ui.pauseMenuText[ui.pauseSelected].setFillColor(sf::Color::Black);
			ui.pauseSelected--;

			if (ui.pauseSelected == -1)
			{
				ui.pauseSelected = 2;
			}

			ui.pauseMenuText[ui.pauseSelected].setFillColor(sf::Color::Red);
		}
	}
}