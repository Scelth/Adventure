#include "GameLogic.hpp"
#include "Collisions.hpp"

void CallMainMenu(sf::RenderWindow& window)
{
    UI mainMenu;
    InitMainMenu(mainMenu);

    bool mainMenuCall = true;

    while (mainMenuCall)
    {
        MainMenuDraw(window, mainMenu);

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
                        if (mainMenu.mainSelected == 0)
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
    sf::Texture tileSetTexture;
    sf::Sprite tileSprite;

    InitGame(gameLogic, tileSetTexture, tileSprite);

    gameLogic.levelDescriptor.levelSymbols = DeserializeLevel();
    gameLogic.levelDescriptor.tileSetTexture = tileSetTexture;
    gameLogic.level = CreateLevel(gameLogic.levelDescriptor, window);

    gameLogic.sound.playGameSound.play();

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::sleep(sf::seconds(0.001f));

        float clockDeltaSeconds = clock.getElapsedTime().asSeconds();
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        HandleWindowEvents(window, gameLogic);

        if (!gameLogic.gamePaused)
        {
            UpdateGame(gameLogic,
                clockDeltaSeconds,
                time,
                window);

            DrawGame(window,
                gameLogic,
                tileSprite);
        }

        else
        {
            PauseMenuDraw(window, gameLogic.ui);
        }
    }
}

void InitGame(GameLogic& gameLogic,
    sf::Texture& tileSetTexture,
    sf::Sprite& tileSprite)
{
    InitUI(gameLogic.ui);

    for (int i = 0; i < ENEMIES_COUNT; ++i)
    {
        InitEnemy(gameLogic.enemies[i]);
        gameLogic.enemies[i].enemyRect.left = ENEMIES_SPAWN_POSITIONS[i][0];
        gameLogic.enemies[i].enemyRect.top = ENEMIES_SPAWN_POSITIONS[i][1];
        gameLogic.enemies[i].enemyRect.width = 85;
        gameLogic.enemies[i].enemyRect.height = 90;
    }

    InitPlayer(gameLogic.player);

    InitLevel(tileSetTexture, tileSprite);
    InitSound(gameLogic.sound);
}

void UpdateGame(GameLogic& gameLogic,
    const float clockDeltaSeconds,
    const float time,
    sf::RenderWindow& window)
{
    GameCamera(gameLogic, window);

    CollisionResult collisionResult;

    // Player
    {
        UpdatePlayer(gameLogic.player, gameLogic.sound, time);

        if (gameLogic.player.playerHealth > 0)
        {
            for (int i = 0; i < ENEMIES_COUNT; ++i)
            {
                gameLogic.enemies[i].enemyHealth = PlayerAttack(gameLogic.player, gameLogic.enemies[i].enemyRect, gameLogic.enemies[i].enemyHealth, gameLogic.sound);
            }
        }

        // Player collision
        CheckCollision(gameLogic.player.playerRect, gameLogic.player.playerVelocity, gameLogic.level, clockDeltaSeconds);

        gameLogic.player.playerVelocity.x = 0.f;
    }

    // Enemies
    for (int i = 0; i < ENEMIES_COUNT; ++i)
    {
        UpdateEnemy(gameLogic.enemies[i], time);

        for (int i = 0; i < ENEMIES_COUNT; ++i)
        {
            if (gameLogic.enemies[i].enemyHealth > 0)
            {
                gameLogic.player.playerHealth = EnemyAttack(gameLogic.enemies[i], gameLogic.player.playerRect, gameLogic.player.playerHealth, gameLogic.sound);
            }
        }

        // Enemies collision
        CheckCollision(gameLogic.enemies[i].enemyRect, gameLogic.enemies[i].enemyVelocity, gameLogic.level, clockDeltaSeconds);

        gameLogic.enemies[i].enemyVelocity.x = 0.f;
    }

    gameLogic.ui.healthText.setString("Your Life: " + std::to_string((int)gameLogic.player.playerHealth));

    if (!IsPlayerAlive(gameLogic.player, gameLogic.sound))
    {
        TurnOffAmbient(gameLogic.sound);

        gameLogic.gamePaused = true;
    }
}

void DrawGame(sf::RenderWindow& window,
    GameLogic& gameLogic,
    const sf::Sprite& tileSprite)
{
    window.clear();

    window.draw(tileSprite);

    for (int i = 0; i < gameLogic.level.tiles.size(); ++i)
    {
        for (int j = 0; j < gameLogic.level.tiles[i].size(); ++j)
        {
            const Tile& tile = gameLogic.level.tiles[i][j];

            sf::Sprite& sprite = gameLogic.level.tileTextureTypeToSprite[tile.textureType];
            sprite.setPosition(TILE_SIZE.x * j, TILE_SIZE.y * i);
            window.draw(sprite);
        }
    }

    for (int i = 0; i < ENEMIES_COUNT; ++i)
    {
        gameLogic.enemies[i].enemySprite.setPosition(gameLogic.enemies[i].enemyRect.left, gameLogic.enemies[i].enemyRect.top);
        window.draw(gameLogic.enemies[i].enemySprite);
    }

    gameLogic.player.playerSprite.setPosition(gameLogic.player.playerRect.left, gameLogic.player.playerRect.top);
    window.draw(gameLogic.player.playerSprite);
    window.draw(gameLogic.ui.healthText);

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

    sf::Vector2f viewCenter = view.getCenter();
    gameLogic.ui.pauseMenuSprite.setPosition(viewCenter.x - 640, viewCenter.y - 360);
    gameLogic.ui.pauseMenuText[0].setPosition(viewCenter.x - 75, viewCenter.y - window.getSize().y / 4.f);
    gameLogic.ui.pauseMenuText[1].setPosition(viewCenter.x - 75, viewCenter.y - window.getSize().y / 16.f);
    gameLogic.ui.pauseMenuText[2].setPosition(viewCenter.x - 50, viewCenter.y + window.getSize().y / 8.f);

    gameLogic.ui.healthText.setPosition(view.getCenter().x - window.getSize().x / 2.f, view.getCenter().y - window.getSize().y / 2.f);

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
                    gameLogic.playerPauseChoice = gameLogic.ui.pauseSelected;

                    if (gameLogic.playerPauseChoice == 0)
                    {
                        TurnOnAmbient(gameLogic.sound);
                        gameLogic.gamePaused = false;
                    }

                    else if (gameLogic.playerPauseChoice == 1)
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