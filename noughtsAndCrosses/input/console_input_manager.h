#pragma once

#include "i_input_manager.h"

namespace ticTacToe
{
	class ConsoleInputManager final : public IInputManager
	{
	public:
		int_fast8_t getNumberPressed() override;
		char getKeyPreseed() override;
		Side letUserSelectSide() override;
		bool askUserIfRestart() override;
	};
}