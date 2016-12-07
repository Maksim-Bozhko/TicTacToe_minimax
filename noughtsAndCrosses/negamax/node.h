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
        Node* getChild(int index);
        Node* findChild(Move move) noexcept;
        Node* findBestChild() noexcept;

        void addChild(Node& child);
        void removeAllChildren() noexcept;

        void evaluate() noexcept;

        BoardState	_boardState;
        int16_t		_childrenOffset; // all children are stored one after another
        int_fast8_t	_childCount;
        int_fast8_t	_bestScore;

        friend class Tree;
    };

    inline Node* Node::getChild(int index)
    {
        assert(0 <= index && index < _childCount);

        return this + _childrenOffset + index;
    }

    inline void Node::addChild(Node& child)
    {
        if (_childCount == 0)
        {
            _childrenOffset = &child - this;
            assert(_childrenOffset >= 0);
        }

        ++_childCount;
        assert(_childCount <= BoardState::_BOARD_SIZE);
    }

    inline void Node::removeAllChildren() noexcept
    {
        _childCount = 0;
    }

    inline void Node::evaluate() noexcept
    {
        _bestScore = _boardState.evaluate();
    }
}