#pragma once

namespace ticTacToe 
{
	class IInputManager 
	{
	public:
		virtual ~IInputManager() noexcept {};

		virtual Move getMove(const Board& board) const = 0;
		virtual Side selectSide() const = 0;
		virtual bool confirmAction() const = 0;
	};
}
