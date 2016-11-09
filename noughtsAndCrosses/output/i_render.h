#pragma once

namespace ticTacToe
{
	class IRender
	{
	public:
		virtual ~IRender() {};
		virtual void drawField(const vec2d& field) = 0;
		virtual void printMessage(std::string message) = 0;
		virtual void clearScreen() = 0;
	};
}