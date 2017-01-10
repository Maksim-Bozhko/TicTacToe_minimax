#pragma once

#include "i_player.h"
#include "negamax/tree.h"

namespace ticTacToe
{
	class AIPlayer final : public IPlayer
	{
	public:
		AIPlayer();
		
		Move makeMove(const Board& board) override;
		void restart() noexcept override;
	
	private:
		std::unique_ptr<Tree> _tree;
	};
}