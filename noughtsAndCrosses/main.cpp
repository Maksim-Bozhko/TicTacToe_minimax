// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include "game/game.h"
#include "output/console_render.h"
#include "input/console_input_manager.h"

int main()
{
    using namespace ticTacToe;

    Game game{ std::make_unique<ConsoleInputManager>(), std::make_unique<ConsoleRender>() };

    game.newGame();

    while (game.restartNeeded())
    {
        game.newGame();
    }

    return 0;
}