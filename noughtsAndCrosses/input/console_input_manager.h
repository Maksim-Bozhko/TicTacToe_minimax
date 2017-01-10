#pragma once

#include "i_input_manager.h"

namespace ticTacToe
{
	class ConsoleInputManager final : public IInputManager
	{
	public:		
		Move getMove(const Board& board) const override;
		Side selectSide() const override;
		bool confirmAction() const override;
	};
}