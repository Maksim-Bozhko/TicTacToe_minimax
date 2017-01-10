#pragma once

namespace ticTacToe
{
	class alignas(16) Node
	{
	public:
		Node() = default;
		Node(const Board& board);

	private:
		Move  getEntryMove() const;
		Node& getChild(int index);
		int   getChildOffset(int index);
		Node* findChild(Move move) noexcept;
		Node* findBestChild() noexcept;

		void  addChild(Node& child);
		void  removeAllChildren() noexcept;

		void  evaluate() noexcept;

		Board		_board;
		int16_t		_childrenOffset; // all children are stored one after another
		int_fast8_t	_childCount { 0 };
		int_fast8_t	_bestScore;

		friend class Tree;
	};

	inline Node& Node::getChild(int index)
	{
		return *(this + _childrenOffset + index);
	}

	inline int Node::getChildOffset(int index)
	{
		return _childrenOffset + index;
	}

	inline void Node::addChild(Node& child)
	{
		if (_childCount == 0)
		{
			_childrenOffset = &child - this;
		}

		++_childCount;
	}

	inline void Node::removeAllChildren() noexcept
	{
		_childCount = 0;
	}

	inline void Node::evaluate() noexcept
	{
		_bestScore = _board.evaluate();
	}
}