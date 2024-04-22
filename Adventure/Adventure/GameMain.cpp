#include "GameLogic.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), GAME_NAME);

    CallMainMenu(window);

    return 0;
}