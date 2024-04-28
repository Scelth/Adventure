#include "UI.hpp"
#include "Constants.hpp"

void InitUI(UI& ui)
{
	ui.menuTexture.loadFromFile(RESOURCES_PATH + "Assets/Menu/Menu.png");
	ui.menuSprite.setTexture(ui.menuTexture);
	ui.pauseMenuTexture.loadFromFile(RESOURCES_PATH + "Assets/Menu/PauseMenu.png");
	ui.pauseMenuSprite.setTexture(ui.pauseMenuTexture);

	ui.uiTextFont.loadFromFile(RESOURCES_PATH + "Fonts/UI.ttf");
	ui.healthText.setFont(ui.uiTextFont);
	ui.healthText.setFillColor(sf::Color::White);

	ui.mainMenuText[0].setFont(ui.uiTextFont);
	ui.mainMenuText[0].setFillColor(sf::Color::Red);
	ui.mainMenuText[0].setString("Play");
	ui.mainMenuText[0].setCharacterSize(50.f);
	ui.mainMenuText[0].setPosition(SCREEN_WIDTH / 2.f - 50.f, SCREEN_HEIGTH / 4.f);

	ui.mainMenuText[1].setFont(ui.uiTextFont);
	ui.mainMenuText[1].setFillColor(sf::Color::Black);
	ui.mainMenuText[1].setString("Exit");
	ui.mainMenuText[1].setCharacterSize(50.f);
	ui.mainMenuText[1].setPosition(SCREEN_WIDTH / 2.f - 50.f, (SCREEN_HEIGTH / 4.f) * 2.3f);

	ui.menuSelected = 0;


	ui.pauseMenuText[0].setFont(ui.uiTextFont);
	ui.pauseMenuText[0].setFillColor(sf::Color::Red);
	ui.pauseMenuText[0].setString("Resume");
	ui.pauseMenuText[0].setCharacterSize(50.f);

	ui.pauseMenuText[1].setFont(ui.uiTextFont);
	ui.pauseMenuText[1].setFillColor(sf::Color::Black);
	ui.pauseMenuText[1].setString("Restart");
	ui.pauseMenuText[1].setCharacterSize(50.f);

	ui.pauseMenuText[2].setFont(ui.uiTextFont);
	ui.pauseMenuText[2].setFillColor(sf::Color::Black);
	ui.pauseMenuText[2].setString("Exit");
	ui.pauseMenuText[2].setCharacterSize(50.f);

	ui.pauseSelected = 0;


	ui.deadMenuText[0].setFont(ui.uiTextFont);
	ui.deadMenuText[0].setFillColor(sf::Color::Red);
	ui.deadMenuText[0].setString("Restart");
	ui.deadMenuText[0].setCharacterSize(50.f);

	ui.deadMenuText[1].setFont(ui.uiTextFont);
	ui.deadMenuText[1].setFillColor(sf::Color::Black);
	ui.deadMenuText[1].setString("Exit");
	ui.deadMenuText[1].setCharacterSize(50.f);

	ui.deadSelected = 0;
}

void DrawUIText(UI& ui,
	sf::RenderWindow& window)
{
	window.draw(ui.healthText);
}

void MainMenuDraw(UI& mainMenu,
	sf::RenderWindow& window)
{
	window.clear();

	window.draw(mainMenu.menuSprite);

	for (int i = 0; i < mainMenu.maxMenuOptions; i++)
	{
		window.draw(mainMenu.mainMenuText[i]);
	}

	window.display();
}

void DeadMenuDraw(UI& ui,
	sf::RenderWindow& window)
{
	window.clear();

	window.draw(ui.menuSprite);

	for (int i = 0; i < ui.maxMenuOptions; i++)
	{
		window.draw(ui.deadMenuText[i]);
	}

	window.display();
}

void PauseMenuDraw(UI& ui,
	sf::RenderWindow& window)
{
	window.clear();

	window.draw(ui.pauseMenuSprite);

	for (int i = 0; i < ui.maxPauseMenuOptions; i++)
	{
		window.draw(ui.pauseMenuText[i]);
	}

	window.display();
}

void MainMenuMove(UI& mainMenu,
	const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Down)
	{
		if (mainMenu.menuSelected + 1 <= mainMenu.maxMenuOptions)
		{
			mainMenu.mainMenuText[mainMenu.menuSelected].setFillColor(sf::Color::Black);
			mainMenu.menuSelected++;

			if (mainMenu.menuSelected == mainMenu.maxMenuOptions)
			{
				mainMenu.menuSelected = 0;
			}

			mainMenu.mainMenuText[mainMenu.menuSelected].setFillColor(sf::Color::Red);
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		if (mainMenu.menuSelected - 1 >= -1)
		{
			mainMenu.mainMenuText[mainMenu.menuSelected].setFillColor(sf::Color::Black);
			mainMenu.menuSelected--;

			if (mainMenu.menuSelected == -1)
			{
				mainMenu.menuSelected = 1;
			}

			mainMenu.mainMenuText[mainMenu.menuSelected].setFillColor(sf::Color::Red);
		}
	}
}

void PauseMenuMove(UI& ui,
	const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Down)
	{
		if (ui.pauseSelected + 1 <= ui.maxPauseMenuOptions)
		{
			ui.pauseMenuText[ui.pauseSelected].setFillColor(sf::Color::Black);
			ui.pauseSelected++;

			if (ui.pauseSelected == ui.maxPauseMenuOptions)
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

void DeadMenuMove(UI& ui,
	const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Down)
	{
		if (ui.deadSelected + 1 <= ui.maxMenuOptions)
		{
			ui.deadMenuText[ui.deadSelected].setFillColor(sf::Color::Black);
			ui.deadSelected++;

			if (ui.deadSelected == ui.maxMenuOptions)
			{
				ui.deadSelected = 0;
			}

			ui.deadMenuText[ui.deadSelected].setFillColor(sf::Color::Red);
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		if (ui.deadSelected - 1 >= -1)
		{
			ui.deadMenuText[ui.deadSelected].setFillColor(sf::Color::Black);
			ui.deadSelected--;

			if (ui.deadSelected == -1)
			{
				ui.deadSelected = 1;
			}

			ui.deadMenuText[ui.deadSelected].setFillColor(sf::Color::Red);
		}
	}
}