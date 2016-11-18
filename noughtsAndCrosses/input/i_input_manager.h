#pragma once

namespace ticTacToe 
{
	class IInputManager 
	{
	public:
		virtual ~IInputManager() noexcept {};

		virtual int getKeyPreseed() const = 0;
		virtual int_fast8_t getDigitPressed() const = 0;
		virtual Side selectSide() const = 0;
		virtual bool confirmAction() const = 0;
	};
}