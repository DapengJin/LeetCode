#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=7 lang=cpp
 *
 * [7] 整数反转
 */

// @lc code=start
class Solution {
public:
    int reverse(int x) {
        int res = 0, min_ = INT_MIN / 10, max_ = INT_MAX / 10; 

        while (x) 
        { 
            // res = max_ 是可以的 (就算 max_ 是地板除)
            // 因为最后一位只能是 0,1,2，不会超过 7 或 8
            if (res > max_ || res < min_) return 0; // overflow

            int digit = x % 10; // 弹出
            x = x /10; 

            res = res * 10 + digit; // 推入
        }

        return res;
    }
};
// @lc code=end

