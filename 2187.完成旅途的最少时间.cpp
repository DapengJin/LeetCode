#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2187 lang=cpp
 *
 * [2187] 完成旅途的最少时间
 */

// @lc code=start
class Solution
{
public:
    long long minimumTime(vector<int> &time, int totalTrips)
    {
        int t_min = INT_MAX;

        for (auto t : time)
            t_min = min(t_min, t);

        // !!! 求出 min max avg 可以缩小范围
        // auto [min_t, max_t] = ranges::minmax(time);
        // int avg = (totalTrips - 1) / time.size() + 1;
        // // 循环不变量：check(left) 恒为 false
        // long long left = (long long)min_t * avg - 1;
        // // 循环不变量：check(right) 恒为 true
        // long long right = min((long long)max_t * avg, (long long)min_t * totalTrips);

        // res 范围 [1, t_min * totalTrips]
        // r 右边表示 sum >= totalTrips
        long long l = 0, r = (long long)t_min * totalTrips + 1; // 左开右开
        //                            !!! int * int = int 溢出 Overflow occurs before assignment!!!

        while (l + 1 < r)
        {
            long long sum = 0, mid = l + (r - l) / 2;

            for (auto t : time)
            {
                sum += mid / t;

                // 防止溢出和优化
                if (sum >= totalTrips)
                    break;
            }

            if (sum >= totalTrips)
                r = mid;
            else
                l = mid;
        }

        return r;
    }
};
// @lc code=end
