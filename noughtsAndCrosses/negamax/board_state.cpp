#include "stdafx.h"

#include "board_state.h"

namespace ticTacToe
{
    const std::array<BitBoard, 8> BoardState::_winningPatterns
    {
        0b111000000u, // top row 448
        0b000111000u, // center row 56
        0b000000111u, // bottom row 7
        0b100100100u, // left column 292 
        0b010010010u, // center column 146
        0b001001001u, // right column 73
        0b100010001u, // diagonal 273
        0b001010100u  // anti-diagonal 84
    };

    Move BoardState::getEntryMove() const noexcept
    {
        return _entryMove;
    }

    vec2d BoardState::getBoard() const noexcept
    {
        vec2d board{ { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

        for (int i = 0; i < _BOARD_SIZE; ++i)
        {
            if (_stones[1].test(i))
            {
                board[i / 3][i % 3] = 1;
            }
            else if (_stones[0].test(i))
            {
                board[i / 3][i % 3] = -1;
            }
        }

        return board;
    }

    bool BoardState::isCrossesTurn() const noexcept
    {
        return _crossesTurn;
    }

    BoardState BoardState::getStartingState()
    {
        BoardState boardState;

        boardState.setStartingState();

        return boardState;
    }

    void BoardState::setStartingState() noexcept
    {
        _stones[0] = 0b000000000;
        _stones[1] = 0b000000000;

        _empty = 0b111111111;

        _crossesTurn = true;

        _entryMove = Move::NO_MOVE;

        _terminal = false;
    }

    bool BoardState::moveIsValid(Move move) const noexcept
    {
        return (Move::NO_MOVE < move) && (move < Move::COUNT) && (_empty.test(move));
    }

    int BoardState::evaluate() noexcept
    {
        // if too little stones on a board to analyze (too many empty places)
        if (_empty.count() > _MAX_EMPTY_FOR_TERMINAL) return Score::DRAW;

        // we analyze from the perspective of player who just made the move, so now it's not his turn to move
        const BitBoard allOurStones{ _stones[!_crossesTurn] };
        const int winningScore{ _crossesTurn ? Score::NOUGHTS_WIN : Score::CROSSES_WIN };

        for (const auto& pattern : _winningPatterns)
        {
            if ((pattern & allOurStones) == pattern)
            {
                _terminal = true;

                return winningScore;
            }
        }

        _terminal = (_empty == 0);

        return Score::DRAW;
    }
}