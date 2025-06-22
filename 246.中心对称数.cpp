#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=246 lang=cpp
 *
 * [246] 中心对称数
 * 
中心对称数是指一个数字在旋转了 180 度之后看起来依旧相同的数字（或者上下颠倒地看）。

请写一个函数来判断该数字是否是中心对称数，其输入将会以一个字符串的形式来表达数字。

 

示例 1:

输入: num = "69"
输出: true
示例 2:

输入: num = "88"
输出: true
示例 3:

输入: num = "962"
输出: false
示例 4：

输入：num = "1"
输出：true


 */

// @lc code=start
class Solution
{
public:
    bool isStrobogrammatic(string num)
    {
        unordered_map<char, char> dict{{'1', '1'}, {'9', '6'}, {'6', '9'}, {'8', '8'}, {'0', '0'}};
        int n = num.size();
        int l = 0, r = n - 1;

        while (l <= r)
        {
            // 数字必须在 dict 里，且 l 和 r 必须是镜像数字
            if (dict.contains(num[r]) && num[l] == dict[num[r]])
            {
                l++;
                r--;
                continue;
            }
            else
                return false;
        }

        return true;
    }
};
// @lc code=end