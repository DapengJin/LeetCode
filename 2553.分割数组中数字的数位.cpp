#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2553 lang=cpp
 *
 * [2553] 分割数组中数字的数位
 */

// @lc code=start
class Solution {
    public:
        vector<int> separateDigits(vector<int>& nums) {
            vector<int> res;
    
            // 从后往前遍历原数组，保证最终结果中每个数字的顺序是按原数组顺序展开的
            for (int i = nums.size() - 1; i >= 0; --i) {
                // 将 nums[i] 拆分为各位数字（从低位到高位）
                while (nums[i]) {
                    res.push_back(nums[i] % 10); // 提取最低位数字
                    nums[i] /= 10;               // 去掉最低位
                }
            }
    
            // 当前 res 中的数字顺序是反的（原数组从后往前 + 每个数字从低位到高位）
            // 所以整体 reverse 一下即可
            reverse(res.begin(), res.end());
    
            return res;
        }
    };
// @lc code=end

