#include "stdafx.h"

#include "console_render.h"

#include <iostream>

namespace ticTacToe
{
	void ConsoleRender::drawField(const vec2d& field)
	{
		clearScreen();

		for (const auto& row : field)
		{
			for (const auto& square : row)
			{
				char symbol = '_';
				switch (square)
				{
				case 1:
					symbol = 'X';
					break;
				case -1:
					symbol = 'O';
					break;
				}
				std::cout << symbol;
			}
			std::cout << std::endl;
		}
	}

	void ConsoleRender::printMessage(std::string message)
	{
		std::cout << message;
	}

	void ConsoleRender::clearScreen()
	{
		system("cls");
	}
}