#pragma once

namespace ticTacToe
{
    class IPlayer
    {
    public:
		virtual ~IPlayer() noexcept {};
		
		virtual Move makeMove(const BoardState& state) = 0;
		virtual void restart() noexcept = 0;
    };
}