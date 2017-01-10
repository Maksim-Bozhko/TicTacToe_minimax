#pragma once

#include "BitBoard.h"

namespace ticTacToe
{
	using vec2d = std::vector<std::vector<int>>;

	class Board
	{
	public:	
		static Board getStartingState();

		Move  getEntryMove() const noexcept;
		vec2d getBoard() const noexcept;
		bool  isCrossesTurn() const noexcept;
		bool  isTerminal() const noexcept;
		bool  destinationIsEmpty(Move move) const noexcept;
		bool  moveIsValid(Move move) const noexcept;
		bool  isWin() noexcept;
		
		int_fast8_t evaluate() noexcept;

		void  setStartingState() noexcept;
		void  change(Move move);

		static constexpr int _BOARD_SIZE { 9 };

	private:
		static const std::array<BitBoard, 8> _winningPatterns;

		// TODO: consider making enum or const
		static std::array<BoardValue, 0b111110000 + 1> _transpositionTable; // key is bitboard, values are 0: unknown, 1: known win, -1: known not win

		std::array<BitBoard, 2>	_stones;
		BitBoard				_empty;
		Move					_entryMove;
		bool					_crossesTurn;
		bool					_terminal;
	};
	
	inline bool Board::isTerminal() const noexcept
	{
		return _terminal;
	}

	inline bool Board::destinationIsEmpty(Move move) const noexcept
	{
		return _empty.test(move);
	}

	inline void Board::change(Move move)
	{
		_empty.reset(move);

		_stones[_crossesTurn].set(move);

		_crossesTurn = !_crossesTurn;

		_entryMove = move;
	}
}