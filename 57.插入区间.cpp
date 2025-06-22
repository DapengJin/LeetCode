#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=57 lang=cpp
 *
 * [57] 插入区间
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> res;
        int i = 0;
        int n = intervals.size();

        // 1. 添加所有在 newInterval 左侧的区间
        while (i < n && intervals[i][1] < newInterval[0])
        {
            res.push_back(intervals[i]);
            i++;
        }

        // 2. 合并所有与 newInterval 有重叠的区间
        while (i < n && intervals[i][0] <= newInterval[1])
        {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        res.push_back(newInterval); // 插入合并后的 newInterval

        // 3. 添加所有在 newInterval 右侧的区间
        while (i < n)
        {
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};
// @lc code=end
