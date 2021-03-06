#pragma once

#include "players/human_player.h"
#include "players/ai_player.h"
#include "output/i_render.h"
#include "input/i_input_manager.h"

namespace ticTacToe
{
	class Game
	{
	public:
		Game(std::unique_ptr<IInputManager> inputManager, std::unique_ptr<IRender> render);

		void newGame();
		bool restartNeeded() const;

	private:
		IPlayer& getCurrentPlayer() noexcept;
		Side selectSide() const;

		void restart() noexcept;

		void gameLoop();

		AIPlayer				 _aiPlayer;
		HumanPlayer				 _humanPlayer;
		Board					 _board;
		std::unique_ptr<IRender> _render;
		bool					 _humanTurnToMove;
	};
}