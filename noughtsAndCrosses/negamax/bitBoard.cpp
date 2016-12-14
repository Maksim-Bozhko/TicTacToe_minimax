#include "stdafx.h"

#include "BitBoard.h"

namespace ticTacToe
{
	BitBoard::BitBoard(storageType bits) noexcept : _bits(bits)
	{
	}

	BitBoard& BitBoard::operator=(storageType bits) noexcept
	{
		_bits = bits;
		
		return *this;
	}
}