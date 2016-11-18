#pragma once

#include <bitset>

namespace ticTacToe
{
	using vec2d = std::vector<std::vector<int_fast8_t>>;

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

		int_fast8_t evaluate() noexcept;

		static constexpr int_fast8_t _BOARD_SIZE { 9 };
		static constexpr int_fast8_t _STONES_TO_WIN { 3 };
		static constexpr int_fast8_t _MAX_EMPTY_FOR_TERMINAL { _BOARD_SIZE - _STONES_TO_WIN - (_STONES_TO_WIN - 1) }; // maximum amount of empty fields for terminal position

	private:
		using BitBoard = std::bitset<_BOARD_SIZE>;

		static const std::array<BitBoard, 8> _winningPatterns;

		std::array<BitBoard, 2>				 _stones;
		BitBoard							 _empty;
		Move								 _entryMove;
		bool								 _crossesTurn;
		bool								 _terminal;
	};

	inline bool BoardState::isTerminal() const noexcept
	{
		return _terminal;
	}

	inline bool BoardState::destinationIsEmpty(Move move) const noexcept
	{
		return _empty[move];
	}

	inline void BoardState::change(Move move)
	{
		assert(Move::NO_MOVE < move && move < _BOARD_SIZE);

		_empty[move] = 0;

		_stones[_crossesTurn][move] = 1;

		_crossesTurn = !_crossesTurn;

		_entryMove = move;
	}
}