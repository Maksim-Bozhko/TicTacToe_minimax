#pragma once

#include "node.h"

namespace ticTacToe
{
	class Tree
	{
	public:
		Tree() noexcept;
		Tree(BoardState& state) noexcept;
		
		Move makeBestMove();

		void restart() noexcept;
		void changeRoot(Move move);

	private:
		Node& addNode(const BoardState& boardState);
		Node& addChild(Node& parent, Move move);

		bool generateMoves(Node& node); // returns true if generates move which leads to terminal state
		void negamax(Node& node, int a, int b, int sign);

		static const std::array<Move, BoardState::_BOARD_SIZE> _moves; // all possible moves
		static constexpr int _MAX_NODES { 4568 }; // 4568 is exactly enough for worst case

		std::vector<Node> _nodes;
		Node*			  _root;
	};
	
	inline Node& Tree::addNode(const BoardState& boardState)
	{
		assert(_nodes.size() < _nodes.capacity()); // reallocation not allowed
		
		_nodes.emplace_back(boardState);

		return _nodes.back();
	}

	inline Node& Tree::addChild(Node& parent, Move move)
	{
		Node& child { addNode(parent._boardState) };

		child._boardState.change(move);

		parent.addChild(child);

		return child;
	}
}