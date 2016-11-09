#pragma once

#include "i_player.h"
#include "input/i_input_manager.h"

namespace ticTacToe
{
	class HumanPlayer final : public IPlayer
	{
	public:
		HumanPlayer(std::shared_ptr<IInputManager> inputManager);
		int_fast8_t makeMove(const BoardState& state) override;
		void restart() noexcept override {};
	private:
		std::shared_ptr<IInputManager> _inputManager;
	};
}