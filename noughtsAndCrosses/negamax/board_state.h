#pragma once

#include <bitset>

namespace ticTacToe
{
	using vec2d = std::vector<std::vector<int_fast8_t>>;

	class BoardState
	{
	public:
		inline bool isCrossesTurn() const noexcept { return _crossesTurn; }

		inline int_fast8_t getEntryMove() const noexcept { return _entryMove; }

		inline bool isTerminal() const noexcept { return _terminal; }

		inline void setStartingState() noexcept
		{
			_stones[0] = 0b000000000;
			_stones[1] = 0b000000000;

			_empty = 0b111111111;

			_crossesTurn = true;

			_entryMove = _NO_MOVE;

			_terminal = false;
		}

		inline void change(int_fast8_t move)
		{
			assert(move > -1 && move < 9);

			_empty[move] = 0;

			_stones[_crossesTurn][move] = 1;

			_crossesTurn = !_crossesTurn;

			_entryMove = move;
		}

		inline bool moveIsValid(int_fast8_t move) const noexcept
		{
			return (move < 9) && (move > -1) && (_empty[move]);
		}

		inline bool destinationIsEmpty(int_fast8_t move) const noexcept { return _empty[move]; }

		int_fast8_t evaluate() noexcept;

		const vec2d getBoard() noexcept;

		static constexpr int_fast8_t _BOARD_SIZE = 9;

		static constexpr int_fast8_t _NO_MOVE = -1;

	private:
		using BitBoard = std::bitset<_BOARD_SIZE>;

		static constexpr std::array<BitBoard, 8> _winningPatterns =
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

		std::array<BitBoard, 2>	_stones;
		BitBoard                _empty;
		int_fast8_t				_entryMove;
		bool                    _crossesTurn;
		bool					_terminal;
	};
}