#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根
 */

// @lc code=start
class Solution
{
public:
    int mySqrt(int x)
    {
        int l = 0, r = min(x, 46340) + 1; 

        while (l + 1 < r) 
        { 
            int mid = l - (l - r) / 2; 

            if (mid > x / mid)
                r = mid; 
            else
                l = mid; 
        }

        return l; 
    }
};
// @lc code=end
