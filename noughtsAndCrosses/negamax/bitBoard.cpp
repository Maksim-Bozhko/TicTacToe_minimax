#include "stdafx.h"

#include "BitBoard.h"

namespace ticTacToe
{
	BitBoard::BitBoard(storageType data) noexcept
	{
		_data = data;
	}

	BitBoard& BitBoard::operator=(storageType data) noexcept
	{
		_data = data;
		
		return *this;
	}
}