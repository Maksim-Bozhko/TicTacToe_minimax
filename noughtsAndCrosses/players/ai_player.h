#pragma once

#include "i_player.h"
#include "negamax/tree.h"

#include <iostream>

namespace ticTacToe
{
	class AIPlayer final : public IPlayer
	{
	public:
		~AIPlayer() {};
		int_fast8_t AIPlayer::makeMove(const BoardState& state) override;
		void restart() noexcept override;
	private:
		Tree _tree;
	};
}