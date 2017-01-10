#pragma once

namespace ticTacToe
{
	// supposed to store bitboard of size up to 16
	class BitBoard
	{
		using storageType = uint16_t;
	public:
		BitBoard() noexcept = default;

		BitBoard(storageType bits) noexcept;

		BitBoard& operator=(storageType bits) noexcept;

		bool test(int pos) const noexcept;

		int count() const noexcept;

		void set(int pos) noexcept;

		void reset(int pos) noexcept;

		friend BitBoard operator&(const BitBoard& lhs, const BitBoard& rhs);

		friend bool operator==(const BitBoard& lhs, const BitBoard& rhs);

		storageType toInt() const noexcept;

	private:
		storageType _bits;
	};

	inline bool BitBoard::test(int pos) const noexcept
	{
		return _bits & (1u << pos);
	}

	inline void BitBoard::set(int pos) noexcept
	{
		_bits |= 1u << pos;
	}

	inline void BitBoard::reset(int pos) noexcept
	{
		_bits &= ~(1u << pos);
	}

	inline int BitBoard::count() const noexcept
	{
		static char table[256] = {
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,

			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,

			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,

			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 };

		return table[_bits		   & 0xFFu] +
			   table[(_bits >> 8u) & 0xFFu]/* +
			   table[(_bits >> 16u) & 0xFFu] +
			   table[(_bits >> 24u)]*/;
	}

	inline BitBoard::storageType BitBoard::toInt() const noexcept
	{
		return _bits;
	}

	inline BitBoard operator&(const BitBoard& lhs, const BitBoard& rhs)
	{
		return lhs._bits & rhs._bits;
	}

	inline bool operator==(const BitBoard& lhs, const BitBoard& rhs)
	{
		return lhs._bits == rhs._bits;
	}
}
