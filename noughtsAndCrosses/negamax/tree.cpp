#include "stdafx.h"

#include "tree.h"

//#include <iostream>
//#include <chrono>
//#include <numeric>

namespace ticTacToe
{
	const std::array<Move, Move::COUNT> Tree::_moves
	{
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

		/*const long long count = 100000;
		std::vector<long long> durations;
		durations.resize(count);
		for (long long i = 0; i < count; ++i)
		{
			auto start = std::chrono::steady_clock::now();
			restart();
			int_fast8_t sign = _root->_boardState.isCrossesTurn() ? 1 : -1;
			negamax(*_root, Score::NOUGHTS_WIN, Score::CROSSES_WIN, sign);
			_root = _root->findBestChild();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
			durations[i] = duration.count();
			std::cout << _root->getEntryMove();
		}

		long long sum { std::accumulate(durations.begin(), durations.end(), 0) };

		std::cout << std::endl << (sum / (double)count);*/

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
		if (generateMoves(node)) return;
		
		for (int i = 0; i < node._childCount; ++i)
		{
			Node& child = *(node._children[i]);

			negamax(child, -b, -a, -sign);

			a = std::max(a, int_fast8_t(sign * child._bestScore));

			if (a >= b) break;
		}

		node._bestScore = a * sign;
	}
}