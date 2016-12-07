#include "stdafx.h"

#include "node.h"

namespace ticTacToe
{
    Node::Node(const BoardState& boardState) : _boardState{ boardState }
    {
    }

    Move Node::getEntryMove() const
    {
        return _boardState.getEntryMove();
    }

    Node* Node::findChild(Move move) noexcept
    {
        for (int i = 0; i < _childCount; ++i)
        {
            Node* child = getChild(i);

            if (child->_boardState.getEntryMove() == move)
            {
                return child;
            }
        }

        return nullptr;
    }

    Node* Node::findBestChild() noexcept
    {
        for (int i = 0; i < _childCount; ++i)
        {
            Node* child = getChild(i);

            if (_bestScore == child->_bestScore)
            {
                return child;
            }
        }

        return nullptr;
    }
}