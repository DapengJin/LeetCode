#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2246 lang=cpp
 *
 * [2246] 相邻字符不同的最长路径
 */

// @lc code=start
class Solution
{
public:
    int longestPath(vector<int> &parent, string s)
    {
        int n = parent.size();
        vector g(n, vector<int>(0));

        for (int i = 1; i < n; i++)
            g[parent[i]].push_back(i);

        int res = 0; // 最少是一个节点

        // !!! return max _边_的数量
        function<int(int)> dfs = [&](int node) -> int
        {
            int x_len = 0; // 储存之前最大的结果

            for (int child : g[node])
            {
                int y_len = dfs(child) + 1;

                if (s[node] != s[child]) // 相邻节点没有分配到相同字符 (没有这行就是模版)
                {
                    // !!! int y_len = dfs(child); 结果不一定经过 parent node
                    res = max(res, x_len + y_len);
                    x_len = max(x_len, y_len);
                }
            }

            return x_len;
        };

        dfs(0);
        return res + 1; // 点的数量是边的数量 +1
    }
};
// @lc code=end
