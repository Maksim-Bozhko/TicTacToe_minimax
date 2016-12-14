#pragma once

#include "node.h"

namespace ticTacToe
{
	class alignas(64) Tree
	{
	public:
		Tree() noexcept;
		Tree(BoardState& state) noexcept;

		Move makeBestMove();

		void changeRoot(Move move);
		void restart() noexcept;

	private:
		Node& addNode(const BoardState& boardState);
		Node& addChild(Node& parent, Move move);

		bool  generateMoves(Node& node); // returns true if generates move which leads to terminal state
		void  negamax(Node& node, int a, int b, int sign);

		static const std::array<Move, Move::COUNT> _moves; // all possible moves
		static constexpr int _MAX_NODES { 4435 }; // 4435 is exactly enough for worst case

		std::array<Node, _MAX_NODES> _nodes;
		Node*						 _root;
		int							 _lastNodeIndex;
	};

	inline Node& Tree::addNode(const BoardState& boardState)
	{
		assert(_lastNodeIndex < _MAX_NODES);

		++_lastNodeIndex;

		_nodes[_lastNodeIndex]._boardState = boardState;

		return	_nodes[_lastNodeIndex];
	}

	inline Node& Tree::addChild(Node& parent, Move move)
	{
		Node& child { addNode(parent._boardState) };

		child._boardState.change(move);

		parent.addChild(child);

		return child;
	}
}