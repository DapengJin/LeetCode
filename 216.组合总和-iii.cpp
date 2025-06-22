#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=216 lang=cpp
 *
 * [216] 组合总和 III
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<int> path;
        vector<vector<int>> res;

        /* 选/不选 */
        function<void(int, int)> dfs = [&](int idx, int target)
        {
            int left = k - path.size();
            
            if (left > idx) return; 

            // (首项 + 末项) * 项数 / 2
            if (target < 0 || target > (idx + idx - left + 1) * left / 2)
                return; 

            if (path.size() == k) // target 只能等于 0 
            {
                res.push_back(path);
                return;
            }

            if (idx == 0) return; 

            dfs(idx - 1, target); 

            path.push_back(idx);
            dfs(idx - 1, target - idx);
            path.pop_back();
        };

        /* 选第几个 */
        // function<void(int, int)> dfs = [&](int idx, int target)
        // {
        //     int left = k - path.size();
            
        //     // (首项 + 末项) * 项数 / 2
        //     if (target < 0 || target > (idx + idx - left + 1) * left / 2)
        //         return; 

        //     if (path.size() == k) // target 只能等于 0 
        //     {
        //         res.push_back(path);
        //         return;
        //     }

        //     // j > left - 1 意思是 选了 j 之后，至少 还要有 left - 1 个数可以选
        //     for (int j = idx; j > left - 1; j--)
        //     {
        //         path.push_back(j);
        //         dfs(j - 1, target - j);
        //         path.pop_back();
        //     }
        // };

        dfs(9, n);

        return res;
    }
};
// @lc code=end
