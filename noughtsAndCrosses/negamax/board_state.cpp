#include "stdafx.h"

#include "board_state.h"

namespace ticTacToe
{
	int_fast8_t BoardState::evaluate() noexcept
	{
		// need at least 4 stones on a board in total
		if (_empty.count() > 5) return Score::DRAW;

		// we analyze from the perspective of player who just made the move, so now it's not his turn to move
		BitBoard	allOurStones = _stones[!_crossesTurn];
		BitBoard	allEnemyStones = _stones[_crossesTurn];
		BitBoard	ourSelectedStones;
		BitBoard	enemySelectedStones;
		int_fast8_t bestScore = Score::DRAW;
		int_fast8_t winningScore = _crossesTurn ? Score::NOUGHTS_WIN : Score::CROSSES_WIN;

		for (const auto& pattern : _winningPatterns)
		{
			ourSelectedStones = pattern & allOurStones;

			if (ourSelectedStones.count() == 3)
			{
				_terminal = true;
				return winningScore;
			}

			enemySelectedStones = pattern & allEnemyStones;

			if (bestScore < Score::FORK && ourSelectedStones.count() == 2 && enemySelectedStones == 0) // we have 2 in a row
				bestScore += Score::INCREMENT;
		}

		if (_empty == 0)
		{
			_terminal = true;
			bestScore = Score::DRAW;
		}
		return bestScore;
	}

	const vec2d BoardState::getBoard() noexcept
	{
		vec2d boardForDrawing = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

		for (int_fast8_t i = 0; i < _BOARD_SIZE; ++i)
		{
			if (_stones[1][i])
				boardForDrawing[i / 3][i % 3] = 1;
			else if (_stones[0][i])
				boardForDrawing[i / 3][i % 3] = -1;
		}

		return boardForDrawing;
	}
}