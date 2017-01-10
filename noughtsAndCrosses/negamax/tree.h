#pragma once

#include "node.h"

namespace ticTacToe
{
	class Tree
	{
	public:
		Tree() noexcept;
		Tree(Board& board) noexcept;

		Move makeBestMove(Board board);

		void changeRoot(Move move);
		void restart(const Board& board = Board::getStartingState()) noexcept;

	private:
		Node& at(int index);
		Node& root();

		void  setRoot(Node& node);

		Node& addNode(Board board);
		Node& addChild(int parent, Move move);

		bool  generateMoves(int node); // returns true if generates move which leads to terminal state
		void  negamax(int node, int a, int b, int sign);

		static const std::array<Move, Board::_BOARD_SIZE> _moves; // all possible moves

		std::vector<Node> _nodes;
		int				  _rootIndex;
	};

	inline Node& Tree::at(int index)
	{
		return _nodes[index];
	}

	inline Node& Tree::root()
	{
		return _nodes[_rootIndex];
	}

	inline void Tree::setRoot(Node& node)
	{
		_rootIndex = &node - _nodes.data();
	}

	inline Node& Tree::addNode(Board board)
	{
		_nodes.emplace_back(board);

		return _nodes.back();
	}

	inline Node& Tree::addChild(int parent, Move move)
	{
		Node& child { addNode(at(parent)._board) };

		child._board.change(move);

		at(parent).addChild(child);

		return child;
	}
}