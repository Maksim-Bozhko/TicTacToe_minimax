#include "stdafx.h"

#include "node.h"

namespace ticTacToe
{
	Node* const Node::findBestChild() const noexcept
	{
		for (int_fast8_t i = 0; i < _childCount; ++i)
			if (_bestScore == _children[i]->_bestScore)
				return _children[i];

		return nullptr;
	}

	Node* const Node::findChildByMove(int_fast8_t move) const noexcept
	{
		for (int_fast8_t i = 0; i < _childCount; ++i)
		{
			Node* child = _children[i];
			if (child->_boardState.getEntryMove() == move) return child;
		}
		
		return nullptr;
	}
}