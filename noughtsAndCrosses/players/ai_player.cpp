#include "stdafx.h"

#include "ai_player.h"

namespace ticTacToe
{
	AIPlayer::AIPlayer() : _tree(std::make_unique<Tree>())
	{
	}
	
	Move AIPlayer::makeMove(const Board& board)
	{	
		return _tree->makeBestMove(board);
	}

	void AIPlayer::restart() noexcept
	{
		_tree->restart();
	};
}

