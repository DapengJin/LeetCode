#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=323 lang=cpp
 *
 * [323] 无向图中连通分量的数目
 */

// @lc code=start
class Solution
{
public:
    int countComponents(int n, vector<vector<int>> &edges)
    {
        int res = 0;
        unordered_set<int> visited;
        unordered_map<int, vector<int>> aj;

        // build aj
        for (auto e : edges)
        {
            int a = e[0], b = e[1];

            aj[a].push_back(b);
            aj[b].push_back(a);
        }

        function<void(int)> dfs = [&](int i)
        {
            if (visited.contains(i))
                return;

            visited.insert(i);

            for (auto child : aj[i])
                dfs(child);
        };

        for (int i = 0; i < n; i++)
        {
            if (!visited.contains(i))
            {
                res++;
                dfs(i);
            }
        }

        return res;
    }
};
// @lc code=end
