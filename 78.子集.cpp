#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> vals;
        int n = nums.size();

        /* 解1: 选 / 不选 */
        // function<void(int)> dfs = [&](int i)
        // {
        //     if (i == n)
        //     {
        //         res.push_back(vals); // copy or move operator
        //         return;
        //     }

        //     // 不选
        //     dfs(i + 1);

        //     // 选 nums[i]
        //     vals.push_back(nums[i]);
        //     dfs(i + 1);
        //     vals.pop_back();
        // };

        /* 解2: 下一个位置选第几个 */
        function<void(int)> dfs = [&](int i)
        {
            res.push_back(vals); 

            // 不用终止条件，长度不可能是 n+1
            
            for (int j = i; j < n; j++)
            {
                vals.push_back(nums[j]);
                dfs(j+1); 
                vals.pop_back();
            }
        }; 

        dfs(0);

        return res;
    }
};
// @lc code=end
