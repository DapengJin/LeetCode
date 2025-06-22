#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */

// @lc code=start
class Solution
{
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;
        vector<int> queens(n);        // 皇后放在 (r,queens[r]) == path
        vector<int> is_cols(n);       // if column[c] has a queen
        vector<int> diag1(2 * n - 1); // r + c 是一个定值
        vector<int> diag2(2 * n - 1); // r - c 是一个定值

        function<void(int)> dfs = [&](int r)
        {
            if (r == n)
            {
                vector<string> board(n);

                for (int i = 0; i < n; i++)
                {
                    board[i] = string(queens[i], '.') + 'Q' +
                               string(n - 1            // 除了 'Q' 之外需要 n-1 个 '.'
                                          - queens[i], // 已经有了 queens[i] 个 '.'
                                      '.');
                }

                res.push_back(board);
                return;
            }

            for (int c = 0; c < n; c++)
            {
                int r_minus_c = r - c + n - 1;

                if (!is_cols[c] && !diag1[r + c] && !diag2[r_minus_c])
                {
                    queens[r] = c; // 记录一下 第 r 行的 queen 是第几列
                    is_cols[c] = diag1[r + c] = diag2[r_minus_c] = true;
                    dfs(r + 1);
                    is_cols[c] = diag1[r + c] = diag2[r_minus_c] = false;
                }
            }
        };

        dfs(0);

        return res;
    }
};
// @lc code=end
class Solution1
{
public:
    void backtracking(vector<vector<string>> &solutions, vector<string> &board,
                      vector<bool> &column, vector<bool> &ldiag, vector<bool> &rdiag, int row)
    {
        int n = board.size();
        if (row == n)
        {
            solutions.push_back(board);
            return;
        }
        for (int i = 0; i < n; ++i)
        {
            if (column[i] || ldiag[n - row + i - 1] || rdiag[row + i])
            {
                continue;
            }

            board[row][i] = 'Q';
            column[i] = ldiag[n - row + i - 1] = rdiag[row + i] = true;
            backtracking(solutions, board, column, ldiag, rdiag, row + 1);
            board[row][i] = '.';
            column[i] = ldiag[n - row + i - 1] = rdiag[row + i] = false;
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        vector<bool> column(n, false);
        vector<bool> ldiag(2 * n - 1, false);
        vector<bool> rdiag(2 * n - 1, false);
        backtracking(solutions, board, column, ldiag, rdiag, 0);
        return solutions;
    }
};