#include "stdafx.h"

#include "console_input_manager.h"

#include <conio.h>

namespace ticTacToe
{
	int_fast8_t ConsoleInputManager::getNumberPressed()
	{
		return _getch() - '0';
	}
	
	char ConsoleInputManager::getKeyPreseed()
	{
		return _getch();
	}
	
	Side ConsoleInputManager::letUserSelectSide()
	{
		char key;
		bool inputIsValid = false;
		
		while (inputIsValid == false)
		{
			key = getKeyPreseed();
			inputIsValid = (key == '1' || key == '2');
		}

		if (key == '1') return Side::CROSSES;
		else			return Side::NOUGHTS;
	}

	bool ConsoleInputManager::askUserIfRestart()
	{
		char key;
		bool inputIsValid = false;
		
		while (inputIsValid == false)
		{
			key = getKeyPreseed();
			key = tolower(key);
			inputIsValid = (key == 'y' || key == 'n');
		}

		return (key == 'y');
	}
}