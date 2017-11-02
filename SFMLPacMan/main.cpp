#include <iostream>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
    Game game(2.5f);
    game.GameLoop();
}

