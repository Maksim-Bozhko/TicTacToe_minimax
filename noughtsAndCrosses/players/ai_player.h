#pragma once

#include "i_player.h"
#include "negamax/tree.h"

#include <iostream>

namespace ticTacToe
{
    class AIPlayer final : public IPlayer
    {
    public:
        Move makeMove(const BoardState& state) override;
        void restart() noexcept override;

    private:
        Tree _tree;
    };
}