#include "stdafx.h"

#include "ai_player.h"

namespace ticTacToe
{
	int_fast8_t AIPlayer::makeMove(const BoardState& state)
	{
		_tree.changeCurrentNode(state.getEntryMove());

		return _tree.makeBestMove();
	}

	void AIPlayer::restart() noexcept
	{
		_tree.restart();
	};
}

