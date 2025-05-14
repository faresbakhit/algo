#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    bool isValidSudoku(vector<vector<char>> &board) {
        array<bool, 9> rowDigits, colDigits, boxDigits;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!invalidateEntry(rowDigits, board[i][j]))
                    return false;
                if (!invalidateEntry(colDigits, board[j][i]))
                    return false;
                if (!invalidateEntry(boxDigits, board[3 * (i / 3) + (j / 3)][3 * (i % 3) + (j % 3)]))
                    return false;
            }
            rowDigits.fill(false);
            colDigits.fill(false);
            boxDigits.fill(false);
        }
        return true;
    }

    bool invalidateEntry(array<bool, 9> &digits, char &entry) {
        if (entry == '.')
            return true;
        bool &digit = digits[entry - '1'];
        if (digit)
            return false;
        digit = true;
        return true;
    }
};

class Solution2 {
public:
    bool isValidSudoku(vector<vector<char>> &board) {
        int32_t digits = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!invalidateEntry<0>(digits, board[i][j]))
                    return false;
                if (!invalidateEntry<9>(digits, board[j][i]))
                    return false;
                if (!invalidateEntry<18>(digits, board[3 * (i / 3) + (j / 3)][3 * (i % 3) + (j % 3)]))
                    return false;
            }
            digits = 0;
        }
        return true;
    }

    template <size_t Offset>
    bool invalidateEntry(int &digits, char &entry) {
        if (entry == '.')
            return true;
        int32_t bitmask = 1 << (entry - '1' + Offset);
        if (digits & bitmask)
            return false;
        digits |= bitmask;
        return true;
    }
};
