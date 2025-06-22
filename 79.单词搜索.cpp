#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 */

// @lc code=start

class Solution
{
    static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
    bool exist(vector<vector<char>> &board, string word)
    {
        int m = board.size(), n = board[0].size();
        auto dfs = [&](this auto &&dfs, int i, int j, int k) -> bool
        {
            if (board[i][j] != word[k]) // 匹配失败
                return false;

            if (k + 1 == word.length()) // 匹配成功！
                return true;

            board[i][j] = 0; // 标记访问过

            for (auto &[dx, dy] : DIRS)
            {
                int x = i + dx, y = j + dy; // 相邻格子

                if (0 <= x && x < m &&
                    0 <= y && y < n && // 没超过边界
                    dfs(x, y, k + 1))  // 并且后续字母都成功匹配
                    return true;
            }

            board[i][j] = word[k]; // 恢复现场

            return false; // 没搜到
        };

        // 每个格子都可以作为起点
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (dfs(i, j, 0))
                    return true; // 搜到了！

        return false; // 没搜到
    }
};
// @lc code=end
