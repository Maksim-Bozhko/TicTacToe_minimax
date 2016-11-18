#include "stdafx.h"

#include "human_player.h"

namespace ticTacToe
{
	HumanPlayer::HumanPlayer(std::unique_ptr<IInputManager> inputManager) : _inputManager { std::move(inputManager) }
	{
	}

	Move HumanPlayer::makeMove(const BoardState& state)
	{
		Move move { Move::NO_MOVE };
		bool moveIsValid { false };

		while (!moveIsValid)
		{
			move = static_cast<Move>(_inputManager->getDigitPressed());
			moveIsValid = state.moveIsValid(move);
		}

		return move;
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

