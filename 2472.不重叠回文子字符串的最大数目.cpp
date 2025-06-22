#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2472 lang=cpp
 *
 * [2472] 不重叠回文子字符串的最大数目
 */

// @lc code=start
class Solution
{
public:
    /**
     * ** DP + 中心拓展
     * 
     * 选不选 s[i] ?
     *  1. 选 
     *      s[i] 是 回文子串中的最后一个，且这个回文子串 >= k
     *      
     *      如何转移 ? 
     *          设 这个回文子串的范围是 [l, r], s[r] == s[i]
     *              [-----f[l-1]----][l---r]
     *          f[r] = f[l-1] + 1
     *          还要看 f[r] 的当前值，所以是：
     *          f[r] = max(f[r], f[l-1] + 1)
     *  2. 不选
     *      f[i] = max(f[i], f[i-1])
     * 
     * 何时更新 f[r] ? 
     *      中心拓展的时候，而不是当 f[i] == f[r] 的时候再查看
     */
    int maxPalindromes(string s, int k)
    {
        int n = s.size(); // 头部添加空串 ""
        // init all 0s
        vector f(n + 1, 0);

        // 中心拓展 [0, 1, 2] 加上中间的两个空隙
        for (int i = 0; i < 2 * n - 1; i++)
        {
            int l = i / 2;
            int r = l + i % 2;

            // f[i] = max(f[i], f[i-1]); // -1 会导致溢出
            f[l + 1] = max(f[l + 1], f[l]);

            for (; l >= 0 && r < n && s[l] == s[r]; l--, r++)
            {
                if (r - l + 1 >= k)
                    // f[r] = max(f[r], f[l-1]); // -1 会导致溢出
                    f[r + 1] = max(f[r + 1], f[l] + 1);
            }
        }

        return f[n];
    }
};
// @lc code=end
