#include "stdafx.h"

#include "tree.h"

namespace ticTacToe
{
	Tree::Tree() noexcept
	{
		restart();
	}

	Tree::Tree(BoardState& state) noexcept
	{
		_currentNode = _allNodes;
		_lastNode = _allNodes;
		_nodesInTotal = 1;

		_currentNode->initialize(state);
	};

	int_fast8_t Tree::makeBestMove()
	{
		assert(_currentNode->_boardState.isTerminal() == false);

		int_fast8_t sign = _currentNode->_boardState.isCrossesTurn() ? 1 : -1;
		negamax(_currentNode, Score::NOUGHTS_WIN, Score::CROSSES_WIN, sign);

		_currentNode = _currentNode->findBestChild();

		return _currentNode->getEntryMove();
	}

	void Tree::changeCurrentNode(int_fast8_t move)
	{
		Node* newNode = _currentNode;

		if (move != BoardState::_NO_MOVE)
			newNode = _currentNode->findChildByMove(move);

		if (newNode == nullptr)
			newNode = addChild(_currentNode, move);

		_currentNode = newNode;
	}

	void Tree::restart() noexcept
	{
		_currentNode = _allNodes;
		_lastNode = _allNodes;
		_nodesInTotal = 1;

		BoardState state;
		state.setStartingState();

		_currentNode->initialize(state);
	}

	// returns true if generates move that leads to terminal state
	bool Tree::generateAndSortMoves(Node* node)
	{
		node->removeAllChildren();
		node->_bestScore = Score::DRAW;

		// order 0 2 4 6 8 1 3 5 7, to check corners and center first
		for (int_fast8_t i = 0; i < BoardState::_BOARD_SIZE * 2; i += 2)
		{
			int_fast8_t move = i % 9;
			if (node->_boardState.destinationIsEmpty(move))
			{
				Node* child = addChild(node, move);
				child->evaluate();
				if (child->_boardState.isTerminal())
				{
					node->_bestScore = child->_bestScore;
					node->swapFirstAndLastChild();
					return true;
				}
				else if (child->_bestScore > node->_bestScore)
				{
					node->_bestScore = child->_bestScore;
					node->swapFirstAndLastChild();
				}
			}
		}
		return false;
	}

	void Tree::negamax(Node* node, int_fast8_t a, int_fast8_t b, int_fast8_t sign)
	{
		if (generateAndSortMoves(node) == false)
		{
			node->_bestScore = a * sign;

			for (int_fast8_t i = 0; i < node->_childCount; ++i)
			{
				Node* child = node->_children[i];

				negamax(child, -b, -a, -sign);

				node->_bestScore = sign*std::max(sign*node->_bestScore, sign*child->_bestScore);

				a = std::max(a, int_fast8_t(sign*child->_bestScore));

				if (a >= b) return;
			}
		}
	}
}