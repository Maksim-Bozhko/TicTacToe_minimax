#pragma once

#include "i_player.h"
#include "input/i_input_manager.h"

namespace ticTacToe
{
	class HumanPlayer final : public IPlayer
	{
	public:
		HumanPlayer(std::unique_ptr<IInputManager> inputManager);
		
		Move makeMove(const BoardState& state) override;
		void restart() noexcept override {};

		bool confirmAction() const;
		Side selectSide() const;
	
	private:
		std::unique_ptr<IInputManager> _inputManager;
	};
}