#include "stdafx.h"

#include "tree.h"

namespace ticTacToe
{
	const std::array<Move, Move::COUNT> Tree::_moves
	{ // it is most efficient to check center and corners first
		CENTER,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		TOP,
		LEFT,
		RIGHT,
		BOTTOM
	};

	Tree::Tree() noexcept
	{
		_nodes.reserve(_MAX_NODES);

		_nodes.emplace_back(BoardState::getStartingState());

		_root = &_nodes.front();

		_root->removeAllChildren();
	}

	Tree::Tree(BoardState& state) noexcept
	{
		_nodes.reserve(_MAX_NODES);

		_nodes.emplace_back(state);

		_root = &_nodes.front();

		_root->removeAllChildren();
	};

	Move Tree::makeBestMove()
	{
		assert(_root->_boardState.isTerminal() == false);
		
		const int sign { _root->_boardState.isCrossesTurn() ? 1 : -1 };

		negamax(*_root, Score::NOUGHTS_WIN, Score::CROSSES_WIN, sign);

		_root = _root->findBestChild();

		return _root->getEntryMove();
	}

	void Tree::restart() noexcept
	{
		_nodes.resize(0);

		_nodes.emplace_back(BoardState::getStartingState());

		_root = &_nodes.front();

		_root->removeAllChildren();
	}

	void Tree::changeRoot(Move move)
	{
		if (move == Move::NO_MOVE) return;

		Node* newNode { _root };

		newNode = _root->findChild(move);

		if (newNode == nullptr) // player made sub optimal move which was pruned away
		{
			newNode = &(addChild(*_root, move));
		}

		_root = newNode;
	}

	bool Tree::generateMoves(Node& node)
	{
		node.removeAllChildren();

		for (const auto& move : _moves)
		{
			if (node._boardState.destinationIsEmpty(move))
			{
				Node* child = &(addChild(node, move));
				
				child->evaluate();
				
				if (child->_boardState.isTerminal())
				{
					node._bestScore = child->_bestScore;
					
					return true;
				}
			}
		}

		return false;
	}

	void Tree::negamax(Node& node, int a, int b, int sign)
	{
		if (generateMoves(node)) return;

		for (int i = 0; i < node._childCount; ++i)
		{
			Node* child = node.getChild(i);

			negamax(*child, -b, -a, -sign);

			a = std::max(a, sign * child->_bestScore);

			if (a >= b) break;
		}

		node._bestScore = a * sign;
	}
}