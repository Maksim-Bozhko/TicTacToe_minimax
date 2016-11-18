#include "stdafx.h"

#include "console_input_manager.h"

#include <conio.h>

namespace ticTacToe
{
	int ConsoleInputManager::getKeyPreseed() const
	{
		return _getch();
	}

	int_fast8_t ConsoleInputManager::getDigitPressed() const
	{
		return static_cast<int_fast8_t>(_getch() - '0');
	}

	Side ConsoleInputManager::selectSide() const
	{
		int key { 0 };
		bool inputIsValid { false };

		while (!inputIsValid)
		{
			key = getKeyPreseed();
			inputIsValid = (key == '1' || key == '2');
		}

		if (key == '1') return Side::crosses;
		else			return Side::noguhts;
	}

	bool ConsoleInputManager::confirmAction() const
	{
		int key { 0 };
		bool inputIsValid { false };

		while (!inputIsValid)
		{
			key = getKeyPreseed();
			key = tolower(key);
			inputIsValid = (key == 'y' || key == 'n');
		}

		return (key == 'y');
	}
}