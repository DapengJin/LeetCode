#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1443 lang=cpp
 *
 * [1443] 收集树上所有苹果的最少时间
 */

// @lc code=start
class Solution
{
public:
    int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
    {
        vector<vector<int>> aj(n, vector<int>());

        for (auto &e : edges)
        {
            int u = e[0], v = e[1];
            aj[u].push_back(v);
            aj[v].push_back(u);
        }

        function<int(int, int)> dfs = [&](int node, int parent) -> int
        {
            int time = 0;

            for (auto child : aj[node])
            {
                if (child == parent)
                    continue; // 防止回头

                // 递归访问子节点
                int child_time = dfs(child, node);

                // 如果子树需要收集苹果，或者子节点本身有苹果
                if (child_time || hasApple[child])
                    // 需要加上从当前节点到子节点的“往返”路径的时间，即 +2
                    time += child_time + 2;
            }

            return time;
        };

        return dfs(0, -1);
    }
};
// @lc code=end
