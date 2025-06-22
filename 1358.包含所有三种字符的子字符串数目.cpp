#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1358 lang=cpp
 *
 * [1358] 包含所有三种字符的子字符串数目
 */

// @lc code=start
class Solution
{
public:
    // 当右端点固定在 right 时，左端点在 0,1,2,…,left−1 的所有子串都是满足要求的，
    // 这一共有 left 个，加到答案中
    int numberOfSubstrings(string s)
    {
        int ans = 0, left = 0; // 左边界
        int cnt[3]{};    // 记录窗口内 'a','b','c' 的出现次数

        for (char c : s)
        {
            cnt[c - 'a']++;

            // 减到 cnt 刚好不够
            while (cnt[0] && cnt[1] && cnt[2])
            {
                cnt[s[left] - 'a']--;
                left++;
            }

            // left 左边的都是满足条件的
            ans += left;
        }

        return ans;
    }
};
// @lc code=end
