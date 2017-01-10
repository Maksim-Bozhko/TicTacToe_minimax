#include "stdafx.h"

#include "game.h"

namespace ticTacToe
{
	Game::Game(std::unique_ptr<IInputManager> inputManager, std::unique_ptr<IRender> render) :
		_humanPlayer(std::move(inputManager)),
		_render { std::move(render) }
	{
		_board.setStartingState();
	}

	void Game::newGame()
	{
		restart();

		_humanTurnToMove = (selectSide() == Side::crosses);

		gameLoop();
	}

	bool Game::restartNeeded() const
	{
		_render->print("Game over. Do you wish to start a new game?(Y/N)");

		return _humanPlayer.confirmAction();
	}

	void Game::gameLoop()
	{
		_render->draw(_board.getBoard());

		while (!_board.isTerminal())
		{
			Move move = getCurrentPlayer().makeMove(_board);

			_board.change(move);

			_board.evaluate(); // TODO: simplify

			_humanTurnToMove = !_humanTurnToMove;

			_render->draw(_board.getBoard());
		}
	}

	void Game::restart() noexcept
	{
		_board.setStartingState();

		_aiPlayer.restart();
		_humanPlayer.restart();
	}

	Side Game::selectSide() const
	{
		_render->clearScreen();

		_render->print("Press 1 to play crosses, 2 to play noughts\n");

		return _humanPlayer.selectSide();
	}

	IPlayer& Game::getCurrentPlayer() noexcept
	{
		if (_humanTurnToMove) return _humanPlayer;
		else				  return _aiPlayer;
	}
}