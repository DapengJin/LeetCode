#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=744 lang=cpp
 *
 * [744] 寻找比目标字母大的最小字母
 */

// @lc code=start
class Solution
{
public:
    char nextGreatestLetter(vector<char> &letters, char target)
    {
        target++; // 大于 target ==> lower_bound(letters, target + 1)
        int n = letters.size();
        int l = -1, r = n;

        // lower bound  target == 'e'
        //   a a c c d  (        )  e e e f f f
        //  小于target   l       r   大于等于target
        while (l + 1 < r)
        {
            int mid = (l + r) / 2;

            if (letters[mid] >= target)
                r = mid;
            else
                l = mid;
        }

        return letters[r % n];
    }
};
// @lc code=end
