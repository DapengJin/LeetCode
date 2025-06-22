#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
class Solution {
    public:
        int maxProduct(vector<int>& nums) {
            int n = nums.size();
            vector<int> f_max(n), f_min(n);

            f_max[0] = f_min[0] = nums[0];

            for (int i = 1; i < n; i++) {
                int x = nums[i];
                
                // 把 x 加到右端点为 i-1 的（乘积最大/最小）子数组后面，
                // 或者单独组成一个子数组，只有 x 一个元素
                f_max[i] = max({f_max[i - 1] * x, f_min[i - 1] * x, x});
                f_min[i] = min({f_max[i - 1] * x, f_min[i - 1] * x, x});
            }

            return ranges::max(f_max);
        }
    };
// @lc code=end

