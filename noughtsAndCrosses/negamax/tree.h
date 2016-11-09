#pragma once

#include "node.h"

namespace ticTacToe
{
	class Tree
	{
	public:
		Tree() noexcept;

		Tree(BoardState& state) noexcept;

		inline int_fast64_t getNodeCount() noexcept { return _nodesInTotal; };

		void restart() noexcept;

		void changeCurrentNode(int_fast8_t move);

		int_fast8_t makeBestMove();

	private:
		inline Node* const addNode()
		{
			++_lastNode;
			++_nodesInTotal;
			assert(_nodesInTotal <= _MAX_NODES);

			return _lastNode;
		}

		inline Node* const addChild(Node* parent, int_fast8_t move)
		{
			Node* const newNode = addNode();

			newNode->initialize(parent->_boardState);
			newNode->_boardState.change(move);

			parent->_children[parent->_childCount] = newNode;
			++(parent->_childCount);
			assert(parent->_childCount <= BoardState::_BOARD_SIZE);

			return newNode;
		}

		inline Node* getNodeByIndex(int16_t index) noexcept
		{
			return &_allNodes[index];
		}

		// returns true if generates move that leads to terminal state
		bool generateAndSortMoves(Node* node);

		void negamax(Node * node, int_fast8_t a, int_fast8_t b, int_fast8_t sign);

		static constexpr int_fast64_t _MAX_NODES = 10000; // 5000 is enough for all cases

		Node		 _allNodes[_MAX_NODES];
		Node*		 _lastNode;
		Node*		 _currentNode;
		int_fast64_t _nodesInTotal; // for debug to know number of nodes
	};
}