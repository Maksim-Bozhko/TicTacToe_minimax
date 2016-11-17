#include "stdafx.h"

#include "board_state.h"

namespace ticTacToe
{
	const std::array<BoardState::BitBoard, 8> BoardState::_winningPatterns =
	{
		0b111000000, // top row 448
		0b000111000, // center row 56
		0b000000111, // bottom row 7
		0b100100100, // left column 292 
		0b010010010, // center column 146
		0b001001001, // right column 73
		0b100010001, // diagonal 273
		0b001010100  // anti-diagonal 84
	};

	Move BoardState::getEntryMove() const noexcept
	{
		return _entryMove;
	}

	vec2d BoardState::getBoard() const noexcept
	{
		vec2d board { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

		for (int_fast8_t i = 0; i < _BOARD_SIZE; ++i)
		{
			if (_stones[1][i])
			{
				board[i / 3][i % 3] = 1;
			}
			else if (_stones[0][i])
			{
				board[i / 3][i % 3] = -1;
			}
		}

		return board;
	}

	bool BoardState::isCrossesTurn() const noexcept
	{
		return _crossesTurn;
	}

	BoardState BoardState::getStartingState()
	{
		BoardState boardState;

		boardState.setStartingState();

		return boardState;
	}

	void BoardState::setStartingState() noexcept
	{
		_stones[0] = 0b000000000;
		_stones[1] = 0b000000000;

		_empty = 0b111111111;

		_crossesTurn = true;

		_entryMove = Move::NO_MOVE;

		_terminal = false;
	}

	bool BoardState::moveIsValid(Move move) const noexcept
	{
		return (Move::NO_MOVE < move) && (move < Move::COUNT) && (_empty[move]);
	}

	int_fast8_t BoardState::evaluate() noexcept
	{
		// if too little stones on a board to analyze (too many empty places)
		if (_empty.count() > _MAX_EMPTY_FOR_TERMINAL) return Score::DRAW;

		// we analyze from the perspective of player who just made the move, so now it's not his turn to move
		const BitBoard	  allOurStones { _stones[!_crossesTurn] };
		const int_fast8_t winningScore { _crossesTurn ? Score::NOUGHTS_WIN : Score::CROSSES_WIN };

		for (const auto& pattern : _winningPatterns)
		{
			BitBoard ourSelectedStones = pattern & allOurStones;

			if (ourSelectedStones.count() == _STONES_TO_WIN)
			{
				_terminal = true;
				return winningScore;
			}
		}

		if (_empty == 0b000000000)
		{
			_terminal = true;
		}

		return Score::DRAW;
	}
}