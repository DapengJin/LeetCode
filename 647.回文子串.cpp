#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=647 lang=cpp
 *
 * [647] 回文子串
 */

// @lc code=start

/**
 * Manacher 算法
 *
 * Manacher算法是一种用于在O(n)时间内求解最长回文子串的问题的算法。
 *      它的核心思想是利用回文的对称性，减少重复计算，从而达到线性时间复杂度。
 *
 * 更直接的说，是找到一个大回文子串的镜像来确定当前字符的初值
 *      （若初值还能拓展，说明它是右端点更大的初值）
 *
 * 维护 维护回文中心 box_m 和其最右端 box_r
 *      若在 box_m，box_r 之内，
 *      可通过 half_len[2 * box_m - i] 直接获得初值（镜像对称）。
 *
 * 中心扩展优化
 *    仅在 i + p[i] > box_r 时，更新 box_m 和 box_r。
 */
class Solution
{
public:
    int countSubstrings(string s)
    {
        // a b a -> ^ # a # b # a # $
        string t = "^";

        for (char c : s)
        {
            t += '#';
            t += c;
        }

        t += "#$";

        vector<int> half_len(t.size() - 2); // 不用算 "#$"

        half_len[1] = 1; // half_len['#'] = 1

        int res = 0;
        //       (--hl--) hl = 2
        // a     b     a
        //    box_m  box_r
        int box_m = 0, box_r = 0;

        // 从第一个 'a' 开始
        for (int i = 2; i < half_len.size(); i++)
        {
            int hl = 1;

            if (i < box_r)
                //          a     b     a
                //    2*box_m-i  box_m  i
                hl = min(half_len[2 * box_m - i],
                         //          a     b     a
                         //                i   box_r
                         box_r - i + 1);

            while (t[i - hl] == t[i + hl])
            {
                hl++;
                box_m = i;
                box_r = i + hl - 1;
            }

            half_len[i] = hl;
            res += hl / 2;
        }

        return res;
    }
};
// @lc code=end

/**
 * 中心拓展 
 * 
 * 考虑 回文 是 奇数 和 偶数 的情况
 * 
 *      a _ a _ a
 * 
 * 中心有可能是 a 或 _。所以总共有 2n - 1 个中心。
 * 
 * for i 属于 [0, 2n-1)
 *      l = i / 2  
 *      r = l + i % 2
 * 
 * 然后开始拓展
 * 
 */
class Solution2
{
public:
    int countSubstrings(string s)
    {
        int n = s.size(), res = 0;

        for (int i = 0; i < 2 * n - 1; i++)
        {
            int l = i / 2, r = l + i % 2;

            while (l >= 0 && r < n && s[l] == s[r])
            {
                l--;
                r++;
                res++;
            }
        }

        return res;
    }
};