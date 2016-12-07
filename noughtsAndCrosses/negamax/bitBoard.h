#pragma once

namespace ticTacToe
{
    // supposed to store bitboard of size up to 32(assuming int is 4 bytes)
    class BitBoard
    {
        using storageType = unsigned int; // 32 int works faster than smaller ints
    public:
        BitBoard() = default;

        BitBoard(storageType data) noexcept;

        BitBoard& operator=(storageType data) noexcept;

        bool test(storageType pos) const noexcept;

        int count() const noexcept;

        void set(storageType pos) noexcept;

        void reset(storageType pos) noexcept;

        friend BitBoard operator&(const BitBoard& lhs, const BitBoard& rhs);

        friend bool operator==(const BitBoard& lhs, const BitBoard& rhs);

    private:
        storageType _data;
    };

    inline bool BitBoard::test(storageType pos) const noexcept
    {
        return _data & (1u << pos);
    }

    inline void BitBoard::set(storageType pos) noexcept
    {
        _data |= 1u << pos;
    }

    inline void BitBoard::reset(storageType pos) noexcept
    {
        _data &= ~(1u << pos);
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

        return table[_data & 0xFFu] +
            table[(_data >> 8u) & 0xFFu];
    }

    BitBoard inline operator&(const BitBoard& lhs, const BitBoard& rhs)
    {
        return lhs._data & rhs._data;
    }

    bool inline operator==(const BitBoard& lhs, const BitBoard& rhs)
    {
        return lhs._data == rhs._data;
    }
}
