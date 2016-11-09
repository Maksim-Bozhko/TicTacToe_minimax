#pragma once

namespace ticTacToe 
{
	class IInputManager 
	{
	public:
		virtual ~IInputManager() {};
		virtual int_fast8_t getNumberPressed() = 0;
		virtual char getKeyPreseed() = 0;
		virtual Side letUserSelectSide() = 0;
		virtual bool askUserIfRestart() = 0;
	};
}
