#include "stdafx.h"

#include "node.h"

namespace ticTacToe
{
	Node::Node(const BoardState& boardState) : _boardState { boardState }
	{
	}

	Move Node::getEntryMove() const
	{
		return _boardState.getEntryMove();
	}

	Node* Node::findChild(Move move) const noexcept
	{
		for (int i = 0; i < _childCount; ++i)
		{
			Node* child = _children[i];

			if (child->_boardState.getEntryMove() == move)
			{
				return child;
			}
		}

		return nullptr;
	}

	Node* Node::findBestChild() const noexcept
	{
		for (int i = 0; i < _childCount; ++i)
		{
			Node* child = _children[i];

			if (_bestScore == child->_bestScore)
			{
				return child;
			}
		}

		return nullptr;
	}
}