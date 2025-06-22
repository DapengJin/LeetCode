#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=245 lang=cpp
 *
 * [245] 最短单词距离 III
 */

// @lc code=start
/* word1 word2 可能相同 */
class Solution
{
public:
    int shortestWordDistance(vector<string> &wordsDict, string word1, string word2)
    {
        int n = wordsDict.size();
        int res = INT_MAX / 2;                  // 求最小 res，定义最大
        int i1 = INT_MIN / 2, i2 = INT_MIN / 2; // idx 从最小开始
        bool is_same = word1 == word2;

        for (int i = 0; i < n; i++)
        {
            if (wordsDict[i] == word1)
            {
                if (is_same) // 如果两个 word 相同，只会 go through 第一个 if
                    swap(i1, i2);

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
