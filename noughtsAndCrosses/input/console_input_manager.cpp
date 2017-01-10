#include "stdafx.h"

#include "console_input_manager.h"

#include <iostream>

namespace ticTacToe
{
	Move ConsoleInputManager::getMove(const Board& board) const
	{
		Move move { Move::NO_MOVE };

		while (!board.moveIsValid(move))
		{
			int input;
			std::cin >> input;
			move = static_cast<Move>(input);
		}

		return move;
	}

	Side ConsoleInputManager::selectSide() const
	{
		int input { 0 };

		while (!(input == 1 || input == 2))
		{
			std::cin >> input;
		}

		if (input == 1) return Side::crosses;
		else			return Side::noguhts;
	}

	bool ConsoleInputManager::confirmAction() const
	{
		char key { 0 };

		while (!(key == 'y' || key == 'n'))
		{
			std::cin >> key;
			key = tolower(key);
		}

		return (key == 'y');
	}
}