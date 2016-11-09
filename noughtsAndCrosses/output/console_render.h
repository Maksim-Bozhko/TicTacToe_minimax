#pragma once

#include "i_render.h"

namespace ticTacToe
{
	class ConsoleRender final : public IRender
	{
	public:
		void drawField(const vec2d& field) override;
		void printMessage(std::string message) override;
		void clearScreen() override;
	};
}