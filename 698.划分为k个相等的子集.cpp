#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=698 lang=cpp
 *
 * [698] 划分为k个相等的子集
 */

// @lc code=start
/**
 * 状态压缩 + 记忆化搜索
 * 
 *      超时是因为重复尝试了很多相同的状态组合
 * 
 * bitmask + memo
 * 
 * 💡 如何判断第 i 个元素有没有被用过？
 *      if ((used_mask >> i) & 1)
 * ✍️ 如何标记一个元素被“用过”？
 *      int next_mask = used_mask | (1 << i);
 * 
 */
class Solution
{
public:
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum % k != 0)
            return false;

        int target = total_sum / k;
        int n = nums.size();

        sort(nums.begin(), nums.end(), greater<int>());

        if (nums[0] > target)
            return false;

        unordered_map<int, bool> memo; // {usedmask : bool}

        function<bool(int, int, int)> dfs = [&](int cur_mask, int cur_sum, int count) -> bool
        {
            if (count == k - 1)
                return true; // 最后一个桶肯定可以成功

            if (memo.contains(cur_mask))
                return memo[cur_mask];

            for (int i = 0; i < n; i++)
            {
                if ((cur_mask >> i) & 1)
                    continue; // i 已经使用过

                int next_sum = cur_sum + nums[i];

                if (next_sum > target)
                    continue; // 不符合条件

                int next_mask = cur_mask | (1 << i);

                if (dfs(next_mask, next_sum % target, count + next_sum / target))
                    return memo[cur_mask] = true;

                if (cur_sum == 0 ||     // 当前正要装一个新的桶，以 nums[i] 开头就已经失败了，后面的数也不用试了
                    next_sum == target) // 当前刚好装满，如果失败，其他组合也不用试了
                    break;
            }

            return memo[cur_mask] = false;
        };

        return dfs(0, 0, 0);
    }
};
// @lc code=end
class Solution1
{
public:
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k)
            return false;

        int target = sum / k;

        if (ranges::max(nums) > target)
            return false;

        int n = nums.size();

        sort(nums.begin(), nums.end(), greater<int>());

        function<bool(int, int, int)> dfs = [&](int i, int K, int s) -> bool
        {
            if (s > target || K < 0)
                return false;
            if (i == n)
            {
                if (K == 0 && s == 0)
                    return true;
                else
                    return false;
            }

            for (int j = i; j < n; j++)
            {
                swap(nums[j], nums[i]);

                int cur_sum = s + nums[i];

                if (cur_sum == target && dfs(i + 1, K - 1, 0))
                    return true;
                else if (dfs(i + 1, K, cur_sum))
                    return true;

                swap(nums[j], nums[i]);
            }

            return false;
        };

        return dfs(0, k, 0);
    }
};