#pragma once

namespace ticTacToe
{
	class Node
	{
	public:
		Node() = default;
		Node(const BoardState& boardState);

	private:
		Move getEntryMove() const;
		Node* findChild(Move move) const noexcept;
		Node* findBestChild() const noexcept;

		void removeAllChildren() noexcept;

		void evaluate() noexcept;

		std::array<Node*, BoardState::_BOARD_SIZE> _children;
		BoardState								   _boardState;
		int_fast8_t								   _childCount;
		int_fast8_t								   _bestScore;

		friend class Tree;
	};

	inline void Node::removeAllChildren() noexcept
	{
		_childCount = 0;
	}

	inline void Node::evaluate() noexcept
	{
		_bestScore = _boardState.evaluate();
	}
}