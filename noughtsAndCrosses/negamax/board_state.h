#pragma once

#include "BitBoard.h"

namespace ticTacToe
{
	using vec2d = std::vector<std::vector<int>>;

	class BoardState
	{
	public:	
		static BoardState getStartingState();

		Move getEntryMove() const noexcept;
		vec2d getBoard() const noexcept;
		bool isCrossesTurn() const noexcept;
		bool isTerminal() const noexcept;
		bool destinationIsEmpty(Move move) const noexcept;
		bool moveIsValid(Move move) const noexcept;

		void setStartingState() noexcept;
		void change(Move move);

		int evaluate() noexcept;

		static constexpr int _BOARD_SIZE { 9 };
		static constexpr int _MAX_EMPTY_FOR_TERMINAL { _BOARD_SIZE - 3 - (3 - 1) }; // maximum amount of empty fields for terminal position

	private:
		static const std::array<BitBoard, 8> _winningPatterns;

		std::array<BitBoard, 2>	_stones;
		BitBoard				_empty;
		Move					_entryMove;
		bool					_crossesTurn;
		bool					_terminal;
	};

	inline bool BoardState::isTerminal() const noexcept
	{
		return _terminal;
	}

	inline bool BoardState::destinationIsEmpty(Move move) const noexcept
	{
		return _empty.test(move);
	}

	inline void BoardState::change(Move move)
	{
		assert(Move::NO_MOVE < move && move < _BOARD_SIZE);

		_empty.reset(move);

		_stones[_crossesTurn].set(move);

		_crossesTurn = !_crossesTurn;

		_entryMove = move;
	}
}