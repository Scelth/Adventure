#include "GameLogic.hpp"
#include "Collisions.hpp"

void CallMainMenu(sf::RenderWindow& window)
{
    UI mainMenu;
    InitUI(mainMenu);

    bool mainMenuCall = true;

    while (mainMenuCall)
    {
        MainMenuDraw(mainMenu, window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Main menu
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up)
                    {
                        MainMenuMove(mainMenu, event);
                    }

                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (mainMenu.menuSelected == 0)
                        {
                            mainMenuCall = false;
                            StartGame(window);
                        }

                        else
                        {
                            mainMenuCall = false;
                            window.close();
                        }
                    }
                }
            }
        }
    }
}

void StartGame(sf::RenderWindow& window)
{
    GameLogic gameLogic;

    InitGame(gameLogic);

    gameLogic.levelDescriptor.levelSymbols = DeserializeLevel();
    gameLogic.level = CreateLevel(gameLogic.levelDescriptor, window);

    gameLogic.sound.playGameSound.play();

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::sleep(sf::seconds(0.001f));

        float clockDeltaSeconds = clock.getElapsedTime().asSeconds();
        float frameTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        frameTime = frameTime / 800.f;

        HandleWindowEvents(window, gameLogic);

        if (!gameLogic.gamePaused)
        {
            UpdateGame(gameLogic,
                clockDeltaSeconds,
                frameTime,
                window);

            DrawGame(window,
                gameLogic);
        }

        else
        {
            if (gameLogic.player.playerHealth > 0.f)
            {
                PauseMenuDraw(gameLogic.ui, window);
            }

            else
            {
                DeadMenuDraw(gameLogic.ui, window);
            }
        }
    }
}

void InitGame(GameLogic& gameLogic)
{
    InitUI(gameLogic.ui);

    for (int i = 0; i < ENEMIES_COUNT; ++i)
    {
        InitEnemy(gameLogic.enemies[i]);
        gameLogic.enemies[i].enemyRect = sf::FloatRect(ENEMIES_SPAWN_POSITIONS[i][0], ENEMIES_SPAWN_POSITIONS[i][1], CHARACTER_RECT_SIZE.x, CHARACTER_RECT_SIZE.y);
    }

    InitPlayer(gameLogic.player);
    InitLevel(gameLogic.map);
    InitSound(gameLogic.sound);
}

void UpdateGame(GameLogic& gameLogic,
    const float clockDeltaSeconds,
    const float frameTime,
    sf::RenderWindow& window)
{
    GameCamera(gameLogic, window);

    // Player
    {
        UpdatePlayer(gameLogic.player, gameLogic.sound, frameTime);

        if (gameLogic.player.playerHealth > 0.f)
        {
            for (int i = 0; i < ENEMIES_COUNT; ++i)
            {
                gameLogic.enemies[i].enemyHealth = PlayerAttack(gameLogic.player, gameLogic.enemies[i].enemyRect, gameLogic.enemies[i].enemyHealth, gameLogic.sound);
            }
        }

        // Player collision
        CheckCollision(gameLogic.player.playerRect, gameLogic.player.playerVelocity, gameLogic.level, clockDeltaSeconds);
    }

    // Enemies
    for (int i = 0; i < ENEMIES_COUNT; ++i)
    {
        UpdateEnemy(gameLogic.enemies[i], frameTime);

        for (int i = 0; i < ENEMIES_COUNT; ++i)
        {
            if (gameLogic.enemies[i].enemyHealth > 0.f)
            {
                gameLogic.player.playerHealth = EnemyAttack(gameLogic.enemies[i], gameLogic.player.playerRect, gameLogic.player.playerHealth, gameLogic.sound);
            }
        }

        // Enemies collision
        CheckCollision(gameLogic.enemies[i].enemyRect, gameLogic.enemies[i].enemyVelocity, gameLogic.level, clockDeltaSeconds);
    }

    gameLogic.ui.healthText.setString("Your Life: " + std::to_string((int)gameLogic.player.playerHealth));

    if (!IsPlayerAlive(gameLogic.player, gameLogic.sound))
    {
        TurnOffAmbient(gameLogic.sound);

        gameLogic.gamePaused = true;
    }
}

void DrawGame(sf::RenderWindow& window,
    GameLogic& gameLogic)
{
    window.clear();

    DrawMap(gameLogic.map, window);

    for (int i = 0; i < ENEMIES_COUNT; ++i)
    {
        DrawEnemy(gameLogic.enemies[i], window);
    }

    DrawPlayer(gameLogic.player, window);
    DrawUIText(gameLogic.ui, window);

    window.display();
}


// Camera
void GameCamera(GameLogic& gameLogic,
    sf::RenderWindow& window)
{
    sf::View view(sf::FloatRect(PLAYER_SPAWN.x, PLAYER_SPAWN.y, window.getSize().x, window.getSize().y));
    sf::Vector2f position = gameLogic.player.playerSprite.getPosition();

    float mapWidth = gameLogic.level.tiles[0].size() * TILE_SIZE.x;
    float mapHeight = gameLogic.level.tiles.size() * TILE_SIZE.y;

    position.x = std::max(position.x, window.getSize().x / 2.f);
    position.y = std::max(position.y, window.getSize().y / 2.f);
    position.x = std::min(position.x, mapWidth - window.getSize().x / 2.f);
    position.y = std::min(position.y, mapHeight - window.getSize().y / 2.f);

    view.setCenter(position);

    gameLogic.ui.pauseMenuSprite.setPosition(view.getCenter().x - (SCREEN_WIDTH / 2.f), view.getCenter().y - (SCREEN_HEIGTH / 2.f));
    gameLogic.ui.pauseMenuText[0].setPosition(view.getCenter().x - 75, view.getCenter().y - window.getSize().y / 4.f);
    gameLogic.ui.pauseMenuText[1].setPosition(view.getCenter().x - 75, view.getCenter().y - window.getSize().y / 16.f);
    gameLogic.ui.pauseMenuText[2].setPosition(view.getCenter().x - 50, view.getCenter().y + window.getSize().y / 8.f);

    gameLogic.ui.healthText.setPosition(view.getCenter().x - window.getSize().x / 2.f, view.getCenter().y - window.getSize().y / 2.f);

    gameLogic.ui.menuSprite.setPosition(view.getCenter().x - (SCREEN_WIDTH / 2.f), view.getCenter().y - (SCREEN_HEIGTH / 2.f));
    gameLogic.ui.deadMenuText[0].setPosition(view.getCenter().x - 75, view.getCenter().y - window.getSize().y / 4.f);
    gameLogic.ui.deadMenuText[1].setPosition(view.getCenter().x - 50, view.getCenter().y + window.getSize().y / 14.f);

    window.setView(view);
}

void HandleWindowEvents(sf::RenderWindow& window,
    GameLogic& gameLogic)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        // Pause menu
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape && !gameLogic.gamePaused)
                {
                    gameLogic.gamePaused = true;
                    PauseAmbient(gameLogic.sound);
                }

                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up)
                {
                    PauseMenuMove(gameLogic.ui, event);
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (gameLogic.ui.pauseSelected == 0)
                    {
                        TurnOnAmbient(gameLogic.sound);
                        gameLogic.gamePaused = false;
                    }

                    else if (gameLogic.ui.pauseSelected == 1)
                    {
                        TurnOffAmbient(gameLogic.sound);

                        gameLogic.gamePaused = false;
                        StartGame(window);
                    }

                    else
                    {
                        window.close();
                    }
                }
            }
        }

        // Dead menu
        {
            if (gameLogic.player.playerHealth < 0.f)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up)
                    {
                        DeadMenuMove(gameLogic.ui, event);
                    }

                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (gameLogic.ui.deadSelected == 0)
                        {
                            TurnOffAmbient(gameLogic.sound);

                            gameLogic.gamePaused = false;
                            StartGame(window);
                        }

                        else
                        {
                            window.close();
                        }
                    }
                }
            }
        }
    }
}