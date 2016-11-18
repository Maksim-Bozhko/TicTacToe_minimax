#pragma once

namespace ticTacToe
{
	class IRender
	{
	public:
		virtual ~IRender() noexcept {};
		
		virtual void draw(const vec2d& board) const = 0;
		virtual void print(const std::string& message) const = 0;
		virtual void clearScreen() const = 0;
	};
}