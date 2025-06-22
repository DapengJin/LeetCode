#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2517 lang=cpp
 *
 * [2517] 礼盒的最大甜蜜度
 */

// @lc code=start
class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        // sort [1,2,5,8,13,21]
        // 单调性：甜蜜度越小，越能选到 k 类，越大 越不能选到 k 类
        //      二分
        // 猜测 res = 7，可以选 1，8，21  -> ok
        // 猜测 res = 9，只能选 1，13，   -> fail
        
        // 确定 答案范围 [0, max - min // (k - 1)]
        ranges::sort(price);

        int n = price.size(), l = -1, r = (price[n-1] - price[0]) + 1; 
        auto check = [&](int mid) -> bool
        {
            int cnt = 1, num = price[0];   

            for (int i = 1; i < n; i++)
            { 
                if (price[i] - num >= mid) 
                {
                    cnt ++; 

                    if (cnt >= k) return true;
                    
                    num = price[i]; 
                }
            }

            return false;
        };

        while (l + 1 < r) 
        { 
            int mid = l + (r - l) / 2; 

            (check(mid) ? l : r) = mid; 
        }

        return l; 
    }
};
// @lc code=end

