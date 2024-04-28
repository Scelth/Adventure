#include "Enemy.hpp"
#include "Collisions.hpp"

void InitEnemy(Enemy& enemy)
{
    enemy.enemyVelocity = sf::Vector2f(0.f, 0.f);

    enemy.enemyTexture.loadFromFile(RESOURCES_PATH + "Assets/Characters/Enemy.png");

    enemy.enemySprite.setTexture(enemy.enemyTexture);
    enemy.enemySprite.setTextureRect(sf::IntRect(0, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
    enemy.enemySprite.setScale(CHARACTER_DRAW_SCALE);
    enemy.enemySprite.setOrigin(CHARACTER_ORIGIN);

    enemy.enemyHealth = 3.f;
}

void DrawEnemy(Enemy& enemy,
    sf::RenderWindow& window)
{
    enemy.enemySprite.setPosition(enemy.enemyRect.left, enemy.enemyRect.top);
    window.draw(enemy.enemySprite);
}

void UpdateEnemy(Enemy& enemy,
    const float frameTime)
{
    enemy.CurrentFrame += 0.006f * frameTime;

    if (enemy.enemyHealth > 0.f)
    {
        enemy.directionChangeCooldown -= 0.05f;

        if (enemy.directionChangeCooldown <= 0.f)
        {
            enemy.direction = rand() % 5; // 0 - Left, 1 - Right, 2 - Down, 3 - Up, 4 - Idle
            enemy.directionChangeCooldown = 10.f;
        }


        switch (enemy.direction)
        {
        case 0:
            if (enemy.CurrentFrame > NUMBERS_OF_FRAME)
            {
                enemy.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            enemy.enemyVelocity.x = -enemy.enemySpeed;
            enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 192, 1152, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
            enemy.enemyLastlDirection = EnemyLastDirection::Left;
            break;

        case 1:
            if (enemy.CurrentFrame > NUMBERS_OF_FRAME)
            {
                enemy.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            enemy.enemyVelocity.x = enemy.enemySpeed;
            enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 192, 192, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
            enemy.enemyLastlDirection = EnemyLastDirection::Right;
            break;

        case 2:
            if (enemy.CurrentFrame > NUMBERS_OF_FRAME)
            {
                enemy.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            enemy.enemyVelocity.y = -enemy.enemySpeed;

            EnemyDirection(enemy);
            break;

        case 3:
            if (enemy.CurrentFrame > NUMBERS_OF_FRAME)
            {
                enemy.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            enemy.enemyVelocity.y = enemy.enemySpeed;

            EnemyDirection(enemy);
            break;

        default:
            enemy.enemyVelocity = sf::Vector2f(0.f, 0.f);

            if (enemy.CurrentFrame > NUMBERS_OF_FRAME)
            {
                enemy.CurrentFrame -= NUMBERS_OF_FRAME;
            }

            EnemyDirection(enemy);
            break;
        }
    }

    else
    {
        if (enemy.CurrentFrame > (NUMBERS_OF_FRAME + 1))
        {
            enemy.CurrentFrame -= (NUMBERS_OF_FRAME + 1);
        }

        enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 128, 1664, 128, 128));

        enemy.enemyVelocity = sf::Vector2f(0.f, 0.f);
    }
}

void EnemyDirection(Enemy& enemy)
{
    if (enemy.enemyLastlDirection == EnemyLastDirection::Left)
    {
        enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 192, 1152, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
    }

    else
    {
        enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 192, 0, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
    }
}

float EnemyAttack(Enemy& enemy,
    sf::FloatRect& playerRect,
    float playerHealth,
    Sound& sound)
{
    if (playerHealth > 0.f)
    {
        if (HandlePlayerEnemyCollision(playerRect, enemy.enemyRect))
        {
            if (playerRect.left > enemy.enemyRect.left)
            {
                enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 192, 384, CHARACTER_SIZE.x, CHARACTER_SIZE.y));
                playerHealth -= 0.00005f;
            }

            else
            {
                enemy.enemySprite.setTextureRect(sf::IntRect(int(enemy.CurrentFrame) * 192, 1344, CHARACTER_SIZE.x, CHARACTER_SIZE.y));

                playerHealth -= 0.00005f;
            }

            if (sound.enemyAttackSound.getStatus() != sf::Sound::Playing)
            {
                sound.enemyAttackSound.play();
            }

            enemy.enemyVelocity = sf::Vector2f(0.f, 0.f);
        }
    }

    return playerHealth;
}