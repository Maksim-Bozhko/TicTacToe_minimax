#pragma once

namespace ticTacToe
{
    class IPlayer
    {
    public:
		virtual ~IPlayer() {};
		virtual int_fast8_t makeMove(const BoardState& state) = 0;
		virtual void restart() noexcept = 0;
    };
}