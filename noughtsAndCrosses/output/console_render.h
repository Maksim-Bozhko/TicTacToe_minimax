#pragma once

#include "i_render.h"

namespace ticTacToe
{
    class ConsoleRender final : public IRender
    {
    public:
        void draw(const vec2d& board) const override;
        void print(const std::string& message) const override;
        void clearScreen() const override;
    };
}