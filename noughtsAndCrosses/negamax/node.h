#pragma once

namespace ticTacToe
{
	class Node
	{
		inline void initialize(BoardState& state) noexcept
		{
			_boardState = state;

			removeAllChildren();
		}

		inline void removeAllChildren() noexcept { _childCount = 0; }

		inline int_fast8_t getEntryMove() const { return _boardState.getEntryMove(); }

		inline void evaluate() noexcept
		{
			_bestScore = _boardState.evaluate();
		}

		inline void swapFirstAndLastChild() noexcept
		{
			if (_childCount > 1)
				std::swap(_children[0], _children[_childCount - 1]);
		}

		Node* const findChildByMove(int_fast8_t move) const noexcept;

		Node* const findBestChild() const noexcept;

		Node*                      _children[BoardState::_BOARD_SIZE];
		BoardState                 _boardState;
		int_fast8_t				   _bestScore;
		int_fast8_t				   _childCount;

		friend class Tree;
	};
}