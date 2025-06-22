#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */

// @lc code=start
class Solution
{
public:
    void bt(vector<int> &nums, vector<vector<int>> &res, int level)
    {
        if (level == nums.size() - 1)
        {
            res.push_back(nums);
            return;
        }

        for (int i = level; i < nums.size(); i++)
        {
            swap(nums[i], nums[level]);
            bt(nums, res, level + 1);
            swap(nums[i], nums[level]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res; 
        int n = nums.size(); 

        // bt(nums, res, 0);

        function<void(int)> dfs = [&](int i)
        {
            if (i == n)
            {
                res.push_back(nums);
                return;
            }

            for (int j = i ; j < n ; j++) // 选一个数放在 i 位置
            {
                swap(nums[i], nums[j]);
                dfs(i+1); 
                swap(nums[i], nums[j]);
            }
        }; 

        dfs(0); 

        return res;
    }
};
// @lc code=end
