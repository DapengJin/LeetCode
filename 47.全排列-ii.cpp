#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        ranges::sort(nums);
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path(n);    // 所有排列的长度都是 n
        vector<int> visited(n); // visited[j] 表示 nums[j] 是否已经填入排列
        // i 表示当前要填排列的第几个数
        auto dfs = [&](this auto &&dfs, int i) -> void
        {
            if (i == n)
            { // 填完了
                ans.push_back(path);
                return;
            }
            // 枚举 nums[j] 填入 path[i]
            for (int j = 0; j < n; j++)
            {
                // 如果 nums[j] 已填入排列，continue
                // 如果 nums[j] 和前一个数 nums[j-1] 相等，且 nums[j-1] 没填入排列，continue
                if (visited[j] || 
                    j > 0 && nums[j] == nums[j - 1] && !visited[j - 1]) // 首未选，则跳过
                {
                    continue;
                }
                path[i] = nums[j];  // 填入排列
                visited[j] = true;  // nums[j] 已填入排列（注意标记的是下标，不是值）
                dfs(i + 1);         // 填排列的下一个数
                visited[j] = false; // 恢复现场
                // 注意 path 无需恢复现场，因为排列长度固定，直接覆盖就行
            }
        };
        dfs(0);
        return ans;
    }
};
// @lc code=end
