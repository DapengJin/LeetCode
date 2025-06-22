#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1343 lang=cpp
 *
 * [1343] 大小为 K 且平均值大于等于阈值的子数组数目
 */

// @lc code=start

/**
 * 定长滑动窗口
 *      入-更新-出
 */
class Solution
{
public:
    int numOfSubarrays(vector<int> &arr, int k, int threshold)
    {
        int ans = 0, sum = 0, n = arr.size(), target = k * threshold;

        for (int i = 0; i < n; i++)
        {
            sum += arr[i];

            // 等于 k-1 的时候 我们窗口内就有足够的元素了
            if (i < k - 1)
                continue;

            if (sum >= target)
                ans++;

            // 移出最前面的元素 i - (k - 1) 就是前面的 k - 1
            sum -= arr[i - k + 1]; // 也可以理解为 i - k 是多减了一个数
        }

        return ans;
    }
};
// @lc code=end
