#include "stdafx.h"

#include "tree.h"

namespace ticTacToe
{
	const std::array<Move, BoardState::_BOARD_SIZE> Tree::_moves { TOP_LEFT, TOP_RIGHT, CENTER, BOTTOM_LEFT, BOTTOM_RIGHT, TOP, LEFT, RIGHT, BOTTOM };

	Tree::Tree() noexcept
	{
		_nodes.reserve(_MAX_NODES);

		_nodes.emplace_back(BoardState::getStartingState());

		_root = &_nodes.front();
	}

	Tree::Tree(BoardState& state) noexcept
	{
		_nodes.reserve(_MAX_NODES);

		_nodes.emplace_back(state);

		_root = &_nodes.front();
	};

	Move Tree::makeBestMove()
	{
		assert(_root->_boardState.isTerminal() == false);

		const int_fast8_t sign { _root->_boardState.isCrossesTurn() ? 1 : -1 };

		negamax(*_root, Score::NOUGHTS_WIN, Score::CROSSES_WIN, sign);

		_root = _root->findBestChild();

		return _root->getEntryMove();
	}

	void Tree::restart() noexcept
	{
		_nodes.resize(0);

		_nodes.emplace_back(BoardState::getStartingState());

		_root = &_nodes.front();
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
				Node& child = addChild(node, move);
				child.evaluate();
				if (child._boardState.isTerminal())
				{
					node._bestScore = child._bestScore;
					return true;
				}
			}
		}

		return false;
	}

	void Tree::negamax(Node& node, int_fast8_t a, int_fast8_t b, int_fast8_t sign)
	{
		if (!generateMoves(node))
		{
			node._bestScore = a * sign;

			for (int i = 0; i < node._childCount; ++i)
			{
				Node* child = node._children[i];

				negamax(*child, -b, -a, -sign);

				node._bestScore = sign * std::max(sign * node._bestScore, sign * child->_bestScore);

				a = std::max(a, int_fast8_t(sign * child->_bestScore));

				if (a >= b) return;
			}
		}
	}
}