#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=547 lang=cpp
 *
 * [547] 省份数量
 */

// @lc code=start
class Solution
{
public:
    void dfs(vector<vector<int>> &isConnected, int i, vector<bool> &visited)
    {
        visited[i] = true;

        for (int j = 0; j < isConnected.size(); j++)
        {   // visited[j] == false since, for isConnected[i][i], visited[i] == true already
            if (visited[j] == false && isConnected[i][j] == 1)
                dfs(isConnected, j, visited);
        }

        return;
    }
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size(), res = 0;
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(isConnected, i, visited);
                res++;
            }
        }

        return res;
    }
};
// @lc code=end
