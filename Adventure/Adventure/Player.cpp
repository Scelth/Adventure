#include "Player.hpp"
#include "Collisions.hpp"

void InitPlayer(Player& player)
{
    player.playerVelocity = sf::Vector2f(0.f, 0.f);

    player.playerTexture.loadFromFile(RESOURCES_PATH + "Assets/Characters/Player.png");

    player.playerSprite.setTexture(player.playerTexture);
    player.playerSprite.setTextureRect(sf::IntRect(0.f, 0.f, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
    player.playerSprite.setScale(CHARACTER_DRAW_SCALE);
    player.playerSprite.setOrigin(CHARACTER_ORIGIN);
    player.playerRect = sf::FloatRect(PLAYER_SPAWN, CHARACTER_RECT_SIZE);

    player.playerHealth = 5.f;
}

void DrawPlayer(Player& player,
    sf::RenderWindow& window)
{
    player.playerSprite.setPosition(player.playerRect.left, player.playerRect.top);
    window.draw(player.playerSprite);
}

void UpdatePlayer(Player& player, Sound& sound,
    const float frameTime)
{
    player.CurrentFrame += 0.006f * frameTime;

    if (player.playerHealth > 0.f)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (player.CurrentFrame > NUMBERS_OF_FRAME)
            {
                player.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            player.playerVelocity.x = -player.playerSpeed;
            player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 1536, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
            player.playerLastDirection = PlayerLastDirection::Left;

            if (sound.walkSound.getStatus() != sf::Sound::Playing)
            {
                sound.walkSound.play();
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (player.CurrentFrame > NUMBERS_OF_FRAME)
            {
                player.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            player.playerVelocity.x = player.playerSpeed;
            player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 192, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
            player.playerLastDirection = PlayerLastDirection::Right;

            if (sound.walkSound.getStatus() != sf::Sound::Playing)
            {
                sound.walkSound.play();
            }
        }

        else
        {
            player.playerVelocity.x = 0.f;

            if (player.CurrentFrame > NUMBERS_OF_FRAME)
            {
                player.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            if (player.playerLastDirection == PlayerLastDirection::Left)
            {
                player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 1728, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
            }

            else
            {
                player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (player.CurrentFrame > NUMBERS_OF_FRAME)
            {
                player.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            player.playerVelocity.y = -player.playerSpeed;

            PlayerDirection(player);

            if (sound.walkSound.getStatus() != sf::Sound::Playing)
            {
                sound.walkSound.play();
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (player.CurrentFrame > NUMBERS_OF_FRAME)
            {
                player.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            player.playerVelocity.y = player.playerSpeed;

            PlayerDirection(player);

            if (sound.walkSound.getStatus() != sf::Sound::Playing)
            {
                sound.walkSound.play();
            }
        }

        else
        {
            player.playerVelocity.y = 0.f;
        }
    }
}

void PlayerDirection(Player& player)
{
    if (player.playerLastDirection == PlayerLastDirection::Left)
    {
        player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 1536, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
    }

    else
    {
        player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 192, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
    }
}

float PlayerAttack(Player& player,
    sf::FloatRect& enemyRect,
    float enemyHealth,
    Sound& sound)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (player.CurrentFrame > NUMBERS_OF_FRAME)
        {
            player.CurrentFrame -= NUMBERS_OF_FRAME;
        }

        player.playerVelocity = sf::Vector2f(0.f, 0.f);

        if (player.playerLastDirection == PlayerLastDirection::Left)
        {
            player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 2112, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
        }

        else
        {
            player.playerSprite.setTextureRect(sf::IntRect(int(player.CurrentFrame) * 192, 576, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
        }

        player.playerAttackArea = sf::FloatRect(player.playerRect.left - PLAYER_ATTACK_RADIUS,
            player.playerRect.top,
            player.playerRect.width + 2.f * PLAYER_ATTACK_RADIUS,
            player.playerRect.height);

        if (HandlePlayerEnemyCollision(player.playerAttackArea, enemyRect))
        {
            if (enemyHealth > 0.f)
            {
                if (sound.playerCritAttackSound.getStatus() != sf::Sound::Playing)
                {
                    sound.playerCritAttackSound.play();
                }

                enemyHealth -= 0.01f;
            }
        }

        else
        {
            if (sound.playerAttackSound.getStatus() != sf::Sound::Playing)
            {
                sound.playerAttackSound.play();
            }
        }
    }

    return enemyHealth;
}

bool IsPlayerAlive(const Player& player, Sound& sound)
{
    if (player.playerHealth < 0.f)
    {
        if (sound.playerDeadSound.getStatus() != sf::Sound::Playing)
        {
            sound.playerDeadSound.play();
        }

        return false;
    }

    return true;
}