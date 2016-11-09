// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include "game/game.h"
#include "output/console_render.h"
#include "input/console_input_manager.h"

int main()
{
	{		
		using namespace ticTacToe;
		using std::unique_ptr;
		
		unique_ptr<IInputManager> inputManager = unique_ptr<ConsoleInputManager>(new ConsoleInputManager);
		unique_ptr<IRender> render = unique_ptr<ConsoleRender>(new ConsoleRender);
		
		Game game(move(inputManager), move(render));
		
		game.newGame();	

		while (game.askUserIfRestart())
		{
			game.newGame();
		}
	}

	return 0;
}