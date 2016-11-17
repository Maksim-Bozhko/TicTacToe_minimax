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
		void negamax(Node& node, int_fast8_t a, int_fast8_t b, int_fast8_t sign);

		static const std::array<Move, BoardState::_BOARD_SIZE> _moves; // all possible moves
		static constexpr int_fast64_t _MAX_NODES { 5500 }; // 5500 is barely enough for worst case

		std::vector<Node>			  _nodes;
		Node*						  _root;
	};

	inline Node& Tree::addNode(const BoardState& boardState)
	{
		_nodes.emplace_back(boardState);

		assert(_nodes.size() <= _MAX_NODES);

		return _nodes.back();
	}

	inline Node& Tree::addChild(Node& parent, Move move)
	{
		Node& newNode { addNode(parent._boardState) };

		newNode._boardState.change(move);

		parent._children[parent._childCount] = &newNode;
		++(parent._childCount);
		assert(parent._childCount <= BoardState::_BOARD_SIZE);

		return newNode;
	}
}