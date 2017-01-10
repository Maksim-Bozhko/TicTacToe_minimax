#include "stdafx.h"

#include "tree.h"

#include <chrono>
#include <iostream>

namespace ticTacToe
{
	const std::array<Move, Move::COUNT> Tree::_moves
	{ // it is most efficient to check center and corners first
		CENTER,
		TOP_LEFT,
		BOTTOM_RIGHT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	Tree::Tree() noexcept
	{
		_nodes.reserve(1024);
		
		restart(Board::getStartingState());
	}

	Tree::Tree(Board& board) noexcept
	{
		_nodes.reserve(1024);
		
		restart(board);
	}

	Move Tree::makeBestMove(Board board)
	{				
		changeRoot(board.getEntryMove());

		root().removeAllChildren();

		const int sign {  root()._board.isCrossesTurn() ? 1 : -1 };

		negamax(_rootIndex, Score::NOUGHTS_WIN, Score::CROSSES_WIN, sign);

		/*const auto beginTime = std::chrono::high_resolution_clock::now();

		int count = 100000;
		for (int i = 0; i < count; ++i)
		{
			restart(Board::getStartingState());

			int sign { root()._board.isCrossesTurn() ? 1 : -1 };

			negamax(_rootIndex, Score::NOUGHTS_WIN, Score::CROSSES_WIN, sign);
		}

		const auto duration = std::chrono::high_resolution_clock::now() - beginTime;

		std::cout << std::endl << duration.count() / double(count);*/
		
		setRoot( *(root().findBestChild()) );

		return root().getEntryMove();
	}

	void Tree::restart(const Board& board) noexcept
	{
		_nodes.resize(0);

		_nodes.emplace_back(board);
		
		_rootIndex = 0;
	}

	void Tree::changeRoot(Move move)
	{
		if (move == Move::NO_MOVE) return;

		Node* newNode { root().findChild(move) };

		if (newNode == nullptr) // player made sub optimal move which was pruned away
		{
			newNode = &(addChild(_rootIndex, move));
		}

		setRoot(*newNode);
	}
	
	bool Tree::generateMoves(int node)
	{	
		for (const auto& move : _moves)
		{
			if (at(node)._board.destinationIsEmpty(move))
			{
				Node& child = addChild(node, move);

				child.evaluate();

				if (child._board.isTerminal())
				{
					at(node)._bestScore = child._bestScore;

					return true;
				}
			}
		}

		return false;
	}
	
	void Tree::negamax(int node, int a, int b, int sign)
	{
		if (generateMoves(node)) return;

		for (int i = 0; i < at(node)._childCount; ++i)
		{
			int child = node + at(node).getChildOffset(i);

			negamax(child, -b, -a, -sign);

			a = std::max(a, sign * at(child)._bestScore);

			if (a >= b) break;
		}

		at(node)._bestScore = a * sign;
	}
}