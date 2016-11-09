#pragma once

namespace ticTacToe
{
	enum class Side
	{
		NOUGHTS,
		CROSSES
	};

	namespace Score {
		//possible score values for evaluate()
		constexpr int_fast8_t CROSSES_WIN = 100;
		constexpr int_fast8_t NOUGHTS_WIN = -100;
		constexpr int_fast8_t DRAW = 0;
		//constexpr int_fast8_t NON_TERMINAL = -1;

		// possible score values for estimateValue()
		constexpr int_fast8_t INCREMENT = 2; // should be in range[2,49]
		constexpr int_fast8_t TWO_IN_A_ROW = DRAW + INCREMENT;
		constexpr int_fast8_t FORK = TWO_IN_A_ROW + INCREMENT;
		//constexpr int_fast8_t SOMEONE_WON = 50;
	};
}