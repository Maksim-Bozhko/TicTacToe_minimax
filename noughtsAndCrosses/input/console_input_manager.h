#pragma once

#include "i_input_manager.h"

namespace ticTacToe
{
	class ConsoleInputManager final : public IInputManager
	{
	public:		
		int getKeyPreseed() const override;
		int_fast8_t getDigitPressed() const override;
		Side selectSide() const override;
		bool confirmAction() const override;
	};
}