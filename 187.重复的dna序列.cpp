#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=187 lang=cpp
 *
 * [187] 重复的DNA序列
 */

// @lc code=start
class Solution
{
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        unordered_map<string, int> counter;
        vector<string> res;
        int n = s.size();

        for (int i = 0; i < n - 10 + 1; i++)
        {
            string sub = s.substr(i, 10);
            counter[sub]++;

            if (counter[sub] == 2)
                res.push_back(sub);
        }

        return res;
    }
};
// @lc code=end
