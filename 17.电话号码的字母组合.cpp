#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start
class Solution {
    string MAPPING[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
public:
    vector<string> letterCombinations(string digits) {
        int n = digits.length();

        if (n == 0) return {};

        vector<string> ans;
        string path(n, 0); // 注意 path 长度一开始就是 n，不是空串

        auto dfs = [&](this auto&& dfs, int i) {
            if (i == n) { // 边界条件
                ans.emplace_back(path);
                return;
            }

            // 枚举
            for (char c : MAPPING[digits[i] - '0']) {
                path[i] = c; // 直接覆盖
                dfs(i + 1);
            }
        };

        dfs(0);

        return ans;
    }
};
// @lc code=end

