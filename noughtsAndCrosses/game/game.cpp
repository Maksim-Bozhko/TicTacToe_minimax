#include "stdafx.h"

#include "game.h"

#include "players/ai_player.h"
#include "players/human_player.h"

namespace ticTacToe
{
	Game::Game(std::unique_ptr<IInputManager> inputManager, std::unique_ptr<IRender> render) :
		_render { std::move(render) },
		_humanPlayer { std::move(inputManager) }
	{
		_boardState.setStartingState();
	}

	void Game::newGame()
	{
		restart();

		const Side userSide { selectSide() };
		_humanTurnToMove = (userSide == Side::crosses);

		gameLoop();
	}

	bool Game::restartNeeded() const
	{
		_render->print("Game over. Do you wish to start a new game?(Y/N)");

		return _humanPlayer.confirmAction();
	}

	void Game::gameLoop()
	{
		_render->draw(_boardState.getBoard());

		while (!_boardState.isTerminal())
		{
			Move move = getCurrentPlayer().makeMove(_boardState);

			_boardState.change(move);

			_boardState.evaluate();

			_humanTurnToMove = !_humanTurnToMove;

			_render->draw(_boardState.getBoard());
		}
	}

	void Game::restart() noexcept
	{
		_boardState.setStartingState();

		_aiPlayer.restart();
		_humanPlayer.restart();
	}

	Side Game::selectSide() const
	{
		_render->clearScreen();

		_render->print("Press 1 to play crosses, 2 to play noughts");

		return _humanPlayer.selectSide();
	}

	IPlayer& Game::getCurrentPlayer() noexcept
	{
		if (_humanTurnToMove) return _humanPlayer;
		else				  return _aiPlayer;
	}
}