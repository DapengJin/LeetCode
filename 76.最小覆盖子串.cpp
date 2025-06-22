#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */

// @lc code=start
class Solution
{
public:
    string minWindow(string s, string t)
    {
        int m = s.length();
        int ans_left = -1, ans_right = m;
        int cnt[128]{};
        int unsatisfied = 0;

        for (char c : t)
        {
            if (cnt[c] == 0)
                unsatisfied++; // 有 unsatisfied 种字母的出现次数 < t 中的字母出现次数

            cnt[c]++;
        }

        int left = 0;

        for (int right = 0; right < m; right++) // 移动子串右端点
        {
            char c = s[right]; // 右端点字母
            cnt[c]--;          // 右端点字母移入子串

            if (cnt[c] == 0) // 原来窗口内 c 的出现次数比 t 的少，现在一样多
                unsatisfied--;

            while (unsatisfied == 0) // 涵盖：所有字母的出现次数都是 >=
            {
                if (right - left < ans_right - ans_left) // 找到更短的子串
                {
                    ans_left = left; // 记录此时的左右端点
                    ans_right = right;
                }

                char x = s[left]; // 左端点字母

                if (cnt[x] == 0)
                {
                    // x 移出窗口之前，检查出现次数，
                    // 如果窗口内 x 的出现次数和 t 一样，
                    // 那么 x 移出窗口后，窗口内 x 的出现次数比 t 的少
                    unsatisfied++;
                }

                cnt[x]++; // 左端点字母移出子串
                left++;
            }
        }
        
        return ans_left < 0 ? "" : s.substr(ans_left, ans_right - ans_left + 1);
    }
};
// @lc code=end

class Solution
{
public:
    string minWindow(string s, string t)
    {
        // sliding window

        // count all chars in t
        unordered_map<char, int> cnt;

        for (auto c : t)
            cnt[c]++;

        // left how many chars left that didn't be covered
        int left = cnt.size();

        int l = 0, n = s.size();
        string res = s + " ";

        // if all of chars in cnt <= 0
        // try to shrink the window to find the min result
        for (int r = 0; r < n; r++)
        {

            if (!cnt.contains(s[r]))
                continue;

            cnt[s[r]]--;

            if (cnt[s[r]] == 0)
                left--;

            if (left == 0) // shrink
            {

                while (l <= r)
                {
                    l++; // !!! in all cases, l needs +1

                    if (!cnt.contains(s[l - 1]))
                        continue;

                    cnt[s[l - 1]]++;

                    if (cnt[s[l - 1]] == 1)
                    {
                        left++;
                        break;
                    }
                }

                res = res.size() > r - l + 2 ? s.substr(l - 1, r - l + 2)
                                             : res;
            }
        }

        return res.size() > s.size() ? "" : res;
    }
};