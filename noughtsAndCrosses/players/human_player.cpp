#include "stdafx.h"

#include "human_player.h"

namespace ticTacToe
{
	HumanPlayer::HumanPlayer(std::shared_ptr<IInputManager> inputManager)
	{
		_inputManager = inputManager;
	}

	int_fast8_t HumanPlayer::makeMove(const BoardState& state)
	{
		int_fast8_t move;
		bool        moveIsValid = false;

		while (moveIsValid == false)
		{
			move = _inputManager->getNumberPressed();
			moveIsValid = state.moveIsValid(move);
		}

		return move;
	}
}

