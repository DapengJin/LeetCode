#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */

// @lc code=start
class Solution
{
public:
    /*
    时间复杂度：
    O(n)，n 表示数组的长度。首先，遍历一遍数组统计元素的频率，这一系列操作的时间复杂度是 O(n)
    桶的数量为 n+1，所以桶排序的时间复杂度为 O(n)
    因此，总的时间复杂度是 O(n)。

    空间复杂度：很明显为 O(n)
    */
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        // {nums:count}
        unordered_map<int, int> counts;

        for (auto num : nums) counts[num]++;

        // {count: [nums]}
        unordered_map<int, vector<int>> buckets;

        for (auto [num, count] : counts) buckets[count].push_back(num);

        vector<int> res; 

        for (int count = nums.size(); res.size() < k; count--)
            if (buckets.contains(count))
                for (int num: buckets[count]) res.push_back(num);

        return res;
    }
};
// @lc code=end
