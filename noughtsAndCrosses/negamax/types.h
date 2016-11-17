#pragma once

namespace ticTacToe
{
	enum class Side : int_fast8_t
	{
		noguhts,
		crosses
	};

	enum Move : int_fast8_t
	{
		NO_MOVE = -1,
		TOP_LEFT = 0,
		TOP,
		TOP_RIGHT,
		LEFT,
		CENTER,
		RIGHT,
		BOTTOM_LEFT,
		BOTTOM,
		BOTTOM_RIGHT,
		COUNT
	};

	namespace Score
	{
		// possible score values for terminal position
		constexpr int_fast8_t NOUGHTS_WIN { -100 };
		constexpr int_fast8_t DRAW { 0 };
		constexpr int_fast8_t CROSSES_WIN { 100 };
	};
}