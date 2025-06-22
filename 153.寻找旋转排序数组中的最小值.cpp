#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=153 lang=cpp
 *
 * [153] 寻找旋转排序数组中的最小值
 */

// @lc code=start
class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int l = -1, r = n - 1, end = nums[n-1];

        while (l + 1 < r)
        {
            int mid = l - (l - r) / 2;

            if (nums[mid] < end)
                r = mid;
            else
                l = mid;
        }

        return nums[r];
    }
};
// @lc code=end

int main()
{
    Solution sol;
    vector<int> test_case = {4, 5, 6, 7, 0, 1, 2};
    cout << "Minimum value: " << sol.findMin(test_case) << endl;
    return 0;
}