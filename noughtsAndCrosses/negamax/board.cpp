#include "stdafx.h"

#include "board.h"

namespace ticTacToe
{
	const std::array<BitBoard, 8> Board::_winningPatterns
	{
		0b001010100u, // anti-diagonal 84
		0b100010001u, // diagonal 273
		0b100100100u, // left column 292
		0b010010010u, // center column 146
		0b111000000u, // top row 448
		0b000111000u, // center row 56
		0b001001001u, // right column 73
		0b000000111u  // bottom row 7
	};

	std::array<BoardValue, 0b111110000 + 1> Board::_transpositionTable { BoardValue::unknown };

	Move Board::getEntryMove() const noexcept
	{
		return _entryMove;
	}

	vec2d Board::getBoard() const noexcept
	{
		vec2d board { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

		for (int i = 0; i < _BOARD_SIZE; ++i)
		{
			if (_stones[1].test(i))
			{
				board[i / 3][i % 3] = 1;
			}
			else if (_stones[0].test(i))
			{
				board[i / 3][i % 3] = -1;
			}
		}

		return board;
	}

	bool Board::isCrossesTurn() const noexcept
	{
		return _crossesTurn;
	}

	Board Board::getStartingState()
	{
		Board board;

		board.setStartingState();

		return board;
	}

	void Board::setStartingState() noexcept
	{
		_stones[0] = 0b000000000;
		_stones[1] = 0b000000000;

		_empty = 0b111111111;

		_crossesTurn = true;

		_entryMove = Move::NO_MOVE;

		_terminal = false;
	}

	bool Board::moveIsValid(Move move) const noexcept
	{
		return (Move::NO_MOVE < move) && (move < Move::COUNT) && (_empty.test(move));
	}

	bool Board::isWin() noexcept
	{
		// we analyze from the perspective of player who just made the move, so now it's not his turn to move
		const BitBoard ourStones { _stones[!_crossesTurn] };
		
		const auto key = ourStones.toInt();
		const auto value = _transpositionTable[key];

		if (value == BoardValue::win) return true;

		if (value == BoardValue::notWin) return false;
		
		for (const auto& pattern : _winningPatterns)
		{
			if ((pattern & ourStones) == pattern)
			{
				_transpositionTable[key] = BoardValue::win;

				return true;
			}
		}

		_transpositionTable[key] = BoardValue::notWin;

		return false;
	}
	
	int_fast8_t Board::evaluate() noexcept
	{	
		if (isWin())
		{
			_terminal = true;

			return _crossesTurn ? Score::NOUGHTS_WIN : Score::CROSSES_WIN;
		}

		_terminal = (_empty == 0);

		return Score::DRAW;
	}
}