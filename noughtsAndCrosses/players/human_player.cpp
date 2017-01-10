#include "stdafx.h"

#include "human_player.h"

namespace ticTacToe
{
	HumanPlayer::HumanPlayer(std::unique_ptr<IInputManager> inputManager) : _inputManager { std::move(inputManager) }
	{
	}

	Move HumanPlayer::makeMove(const Board& board)
	{
		return _inputManager->getMove(board);
	}

	bool HumanPlayer::confirmAction() const
	{
		return _inputManager->confirmAction();
	}

	Side HumanPlayer::selectSide() const
	{
		return _inputManager->selectSide();
	}
}

