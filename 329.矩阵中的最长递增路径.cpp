#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=329 lang=cpp
 *
 * [329] 矩阵中的最长递增路径
 */

// @lc code=start
class Solution
{
public:
    /**
     * 不需要记录具体路径
     * 
     * 1. 状态转移只依赖邻居“最优解”，无须回退修改状态 （path.pop_back()）
	 *      在回溯里，我们常常要做“选择——递归——撤销选择”三步，来保证 path 能正确回到上一个状态。
	 *      而在本题中，dfs 返回的就是「从当前格子出发的最长长度」，
     *      调用端只用 1 + dfs(neighbor) 即可，不需要在递归里改动全局或者共享变量，
     *      也不需要显式“撤销”。
     * 
     * 
     * 2. 由于题目要求的是「严格递增路径」，也就是说沿着路径走，
     *      后继节点的值必然大于前继节点的值，因此不存在「回头」或「环路」的可能性。
     *      你只要知道从当前节点出发能走多远就行，不需要维护一个访问过的节点列表或把节点
     *      逐个 push_back/pop_back 到 path 里去。
     */
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo(m, vector<int>(n, INT_MAX));
        int dir[5] = {1, 0, -1, 0, 1};

        function<int(int, int)> dfs = [&](int i, int j) -> int
        {
            if (memo[i][j] != INT_MAX)
                return memo[i][j];

            int max_len = 1;

            for (int k = 0; k < 4; k++)
            {
                int x = i + dir[k], y = j + dir[k + 1];

                if (x >= 0 && x < m && y >= 0 && y < n && // 越界检查
                    matrix[x][y] > matrix[i][j])          // 保证严格递增
                    // 从邻居出发，再加上自己这一步
                    max_len = max(max_len, 1 + dfs(x, y));
            }

            return memo[i][j] = max_len;
        };

        int res = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res = max(res, dfs(i, j));

        return res;
    }
};
// @lc code=end
