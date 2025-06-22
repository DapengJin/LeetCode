#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1964 lang=cpp
 *
 * [1964] 找出到每个位置为止最长的有效障碍赛跑路线
 */

// @lc code=start
class Solution
{
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles)
    {
        int n = obstacles.size();
        vector<int> g, res;

        for (auto x : obstacles)
        {
            auto it = ranges::upper_bound(g, x);

            res.push_back(it - g.begin() + 1); // !!! vector 改变之后 iter 就失效了

            if (it == g.end())
                g.push_back(x);
            else
                *it = x;
            
            // !!! res 不能放在这里更新
        }

        return res;
    }
};
// @lc code=end
