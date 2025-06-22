#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=410 lang=cpp
 *
 * [410] 分割数组的最大值
 */

// @lc code=start
class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        int n = nums.size();

        auto check = [&](int mx)
        {
            int cnt = 1; // # segments
            int sum = 0;

            for (auto num : nums)
            {
                if (num > mx)
                    return false;

                sum += num;

                if (sum > mx)
                {
                    cnt++;
                    sum = num;
                }

                if (cnt > k)
                    return false;
            }

            return true;
        };

        // res range [min(nums), sum(nums)]
        int l = ranges::max(nums) - 1;
        // right side satisfies the check
        int r = accumulate(nums.begin(), nums.end(), 0) + 1; 

        while (l + 1 < r)
        {
            int mid = l - (l - r) / 2;

            if (check(mid))
                r = mid;
            else
                l = mid;
        }

        return r;
    }
};
// @lc code=end
class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        int res = INT_MAX;
        vector<int> path;
        int n = nums.size();

        function<void(int, int)> dfs = [&](int i, int k)
        {
            if (k == 0 && i == n)
            {
                res = min(res, ranges::max(path));
                return;
            }

            int sum = 0;

            for (int j = i; j < n; j++)
            {
                sum += nums[j];

                path.push_back(sum);
                dfs(j + 1, k - 1);
                path.pop_back();
            }
        };

        dfs(0, k);

        return res;
    }
};