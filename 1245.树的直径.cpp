#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=337 lang=cpp
 *
 * [1245] 树的直径
 */

// @lc code=start
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        int n = edges.size(), res = 0; 
        unordered_map<int, vector<int>> g; 

        for (int i = 0; i < n ; i++)
        {
            int u = edges[i][0], v = edges[i][1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        function<int(int, int)> dfs = [&] (int node, int father) -> int 
        {
            int max_len = 0;

            for (int child : g[node])
            { 
                if (child == father) continue; 

                int len = dfs(child, node) + 1; 
                res = max(res, max_len + len) ;
                max_len = max(max_len, len); 
            }

            return max_len; 
        }; 

        dfs(0, -1);
        return res; 
    }
};
// @lc code=end