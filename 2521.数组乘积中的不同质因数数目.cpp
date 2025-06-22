#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2521 lang=cpp
 *
 * [2521] 数组乘积中的不同质因数数目
 */

// @lc code=start
class Solution
{
public:
    int distinctPrimeFactors(vector<int> &nums)
    {
        // 时间 O(n * sqrt(max(nums)))
        // 空间 O(U / log U) 素数分布
        
        unordered_set<int> s;

        for (auto num : nums)
        {
            int i = 2, x = num;

            while (i * i <= num)
            {
                if (x % i == 0)
                {
                    s.insert(i); // don't need to inserted repeatedly

                    do
                        x = x / i;
                    while (x % i == 0);
                }

                i++;
            }

            if (x > 1)
                s.insert(x); // !!! 剩下的 x 也是质因数
        }

        return s.size();
    }
};
// @lc code=end
