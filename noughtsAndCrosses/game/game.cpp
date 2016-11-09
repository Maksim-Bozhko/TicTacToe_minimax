#include "stdafx.h"

#include "game.h"

#include "players/ai_player.h"
#include "players/human_player.h"

namespace ticTacToe
{
	Game::Game(std::unique_ptr<IInputManager> inputManager, std::unique_ptr<IRender> render) :
		_inputManager(std::move(inputManager)),
		_render(std::move(render)),
		_humanPlayer(_inputManager)
	{
		_boardState.setStartingState();
	}

	void Game::newGame()
	{
		Side userSide = letUserSelectSide();
		_humanTurnToMove = (userSide == Side::CROSSES);

		restart();

		gameLoop();
	}

	void Game::gameLoop()
	{
		_render->drawField(_boardState.getBoard());

		while (_boardState.isTerminal() == false)
		{
			int_fast8_t move = getCurrentPlayer()->makeMove(_boardState);

			_boardState.change(move);

			_boardState.evaluate();

			_humanTurnToMove = !_humanTurnToMove;

			_render->drawField(_boardState.getBoard());
		}
	}

	void Game::restart() noexcept
	{
		_boardState.setStartingState();

		_aiPlayer.restart();
		_humanPlayer.restart();
	}

	IPlayer* Game::getCurrentPlayer() noexcept
	{
		if (_humanTurnToMove) return (&_humanPlayer);
		else				  return (&_aiPlayer);
	}

	Side Game::letUserSelectSide()
	{
		_render->clearScreen();

		_render->printMessage("Press 1 to play crosses, 2 to play noughts");

		return _inputManager->letUserSelectSide();
	}

	bool Game::askUserIfRestart()
	{
		_render->printMessage("Game over. Do you wish to start a new game?(Y/N)");

		return _inputManager->askUserIfRestart();
	}
}