#include "stdafx.h"

#include "ai_player.h"

namespace ticTacToe
{
	Move AIPlayer::makeMove(const BoardState& state)
	{	
		_tree.changeRoot(state.getEntryMove());

		return _tree.makeBestMove();
	}

	void AIPlayer::restart() noexcept
	{
		_tree.restart();
	};
}

