#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=149 lang=cpp
 *
 * [149] 直线上最多的点数
 */

// @lc code=start
class Solution
{
public:
    // 统计一个点到其他各个点的斜率
    int maxPoints(vector<vector<int>> &points)
    {
        unordered_map<string, int> m;
        int n = points.size();

        if (n <= 2)
            return n;

        int res = 2;

        for (int i = 0; i < n - 1; i++)
        {
            int x1 = points[i][0], y1 = points[i][1];

            for (int j = i + 1; j < n; j++)
            {
                int x2 = points[j][0], y2 = points[j][1];
                int y_ = y1 - y2, x_ = x1 - x2;

                if (x_ == 0)
                {
                    m["inf"]++;
                    continue;
                }

                int gcd = __gcd(y_, x_);
                y_ /= gcd;
                x_ /= gcd;

                if (x_ < 0)
                {
                    x_ = -x_;
                    y_ = -y_;
                }

                m[to_string(y_) + "/" + to_string(x_)]++;
            }

            for (auto [s, cnt] : m)
                res = max(res, cnt + 1);
            
            m = {}; 
        }

        return res;
    }
};
// @lc code=end
