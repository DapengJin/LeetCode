#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=90 lang=cpp
 *
 * [90] 子集 II
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end()); // ⭐️ 排序是关键
        vector<int> path;
        vector<vector<int>> res;
        int n = nums.size();
        vector<bool> visited(n, false);

        function<void(int)> dfs = [&](int i)
        {
            if (i == n)
            {
                res.push_back(path);
                return; // ⭐️ 这里要 return，防止 i 超出范围
            }

            // 不选 nums[i]
            visited[i] = false;
            dfs(i + 1);

            // 选 nums[i]
            // ⭐️ 去重条件：当前和前一个相同，但前一个没有被选中
            if (i > 0 && nums[i] == nums[i - 1] && visited[i - 1] == false)
                return;

            path.push_back(nums[i]);
            visited[i] = true;
            dfs(i + 1);
            path.pop_back();
        };

        dfs(0);
        return res;
    }
};
// @lc code=end
class Solution
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> path;

        // 为了去重，先排序，确保重复元素相邻
        sort(nums.begin(), nums.end());

        // 回溯函数，start 表示从哪一位开始选
        function<void(int)> dfs = [&](int start)
        {
            // 每个节点（即递归中的一条路径）都是一个子集
            res.push_back(path);

            for (int i = start; i < nums.size(); ++i)
            {
                // 树层去重：同一层中，如果当前值等于上一个值，则跳过
                if (i > start && nums[i] == nums[i - 1])
                    continue;

                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back();
            }
        };

        dfs(0);
        
        return res;
    }
};
