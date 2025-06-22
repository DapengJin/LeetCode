#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=243 lang=cpp
 *
 * [243] 最短单词距离
 */

// @lc code=start
class Solution
{
public:
    int shortestDistance(vector<string> &wordsDict, string word1, string word2)
    {
        int n = wordsDict.size();
        int res = INT_MAX / 2;                  // 求最小 res，定义最大
        int i1 = INT_MIN / 2, i2 = INT_MIN / 2; // idx 从最小开始

        for (int i = 0; i < n; i++)
        {
            if (wordsDict[i] == word1)
            {
                if (i1 < i2) // 如果 i2 < i1，那么 i2 肯定小于 i
                    res = min(res, abs(i - i2));

                i1 = i;
            }
            else if (wordsDict[i] == word2)
            {
                if (i1 > i2)
                    res = min(res, abs(i - i1));

                i2 = i;
            }
        }

        return res;
    }
};
// @lc code=end
