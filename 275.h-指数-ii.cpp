#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=275 lang=cpp
 *
 * [275] H 指数 II
 */

// @lc code=start
class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        // 在区间 (left, right) 内询问
        int n = citations.size();
        int l = 0, r = n + 1;

        while (l + 1 < r) // 区间不为空
        {
            // 循环不变量：
            // left  左边的回答一定为「是」
            // right 右边的回答一定为「否」
            // 注意!!! mid 表示的是 答案范围 [0, n] 内 寻找答案，而不是表示 citations 的 index
            int mid = l + (r - l) / 2; // 是否有 mid 篇论文引用次数 >= mid

            // 引用次数最多的 mid 篇论文，引用次数均 >= mid
            if (citations[n - mid] >= mid)
                l = mid; // 询问范围缩小到 (mid, right)
            else
                r = mid; // 询问范围缩小到 (left, mid)
        }

        // 根据循环不变量，left 左边现在是最大的回答为「是」的数
        return l;
    }
};
// @lc code=end
