#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res; 
        vector<int> path; 
        int n = candidates.size(); 

        // 选/不选
        function<void(int, int)> dfs = [&](int i, int left) 
        { 
            if (left == 0) 
            {
                res.push_back(path); 
                return;
            }

            if (i == n || left < 0) 
                return; 

            // 选
            path.push_back(candidates[i]); 
            dfs(i, left - candidates[i]); 
            // dfs(i + 1, left - candidates[i]); // !!! 包含在 先选后不选里了 重复
            path.pop_back(); 

            // 不选
            dfs(i+ 1, left); 
        }; 

        dfs(0, target); 

        return res; 
    }
};
// @lc code=end

