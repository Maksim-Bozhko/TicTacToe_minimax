#include "stdafx.h"

#include "console_render.h"

#include <iostream>

namespace ticTacToe
{
	void ConsoleRender::draw(const vec2d& board) const
	{
		clearScreen();

		for (const auto& row : board)
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

	void ConsoleRender::print(const std::string& message) const
	{
		std::cout << message;
	}

	void ConsoleRender::clearScreen() const
	{
		system("cls");
	}
}