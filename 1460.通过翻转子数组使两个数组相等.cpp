#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1460 lang=cpp
 *
 * [1460] 通过翻转子数组使两个数组相等
 */

// @lc code=start
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        // python: 
        //      return Counter(target) == Counter(arr)

        unordered_map<int, int> counts1, counts2;
        for (int num : target) {
            counts1[num]++;
        }
        for (int num : arr) {
            counts2[num]++;
        }
        if (counts1.size() != counts2.size()) {
            return false;
        }
        for (auto &[key, value] : counts1) {
            if (!counts2.count(key) || counts2[key] != value) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

