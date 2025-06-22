#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1105 lang=cpp
 *
 * [1105] 填充书架
 */

// @lc code=start
class Solution
{
public:
/*
 * https://leetcode.cn/problems/filling-bookcase-shelves/solutions/2240688/jiao-ni-yi-bu-bu-si-kao-dong-tai-gui-hua-0vg6/
 *
 * 一共7本书，假设这一层放了 4 本书（也可以是假设放了 3 本，2 本，1 本），
 * 那么剩余的要解决的问题是 books 的前 3 本书按顺序摆放后的最小高度。
 * 
 * 由于这是一个和原问题相似的子问题，所以可以用递归解决。
 * 
 * dfs(i) 表示把 books[0] 到 books[i] 按顺序摆放后的最小高度。
 * 
 * 

// 暴力递归，会超时
class Solution {
public:
    int minHeightShelves(vector<vector<int>> &books, int shelf_width) {
        function<int(int)> dfs = [&](int i) -> int {
            if (i < 0) return 0; // 没有书了，高度是 0
            int res = INT_MAX, max_h = 0, left_w = shelf_width;
            for (int j = i; j >= 0; --j) {
                left_w -= books[j][0];
                if (left_w < 0) break; // 空间不足，无法放书
                max_h = max(max_h, books[j][1]); // 从 j 到 i 的最大高度
                res = min(res, dfs(j - 1) + max_h);
            }
            return res;
        };
        return dfs(books.size() - 1);
    }
};

 *
 */
    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
        int n = books.size(), f[n + 1];
        f[0] = 0; // 翻译自 dfs(-1)=0

        for (int i = 0; i < n; ++i) {
            f[i + 1] = INT_MAX;
            int max_h = 0, left_w = shelfWidth;
            
            for (int j = i; j >= 0; --j) {
                left_w -= books[j][0];

                if (left_w < 0) break; // 空间不足，无法放书

                max_h = max(max_h, books[j][1]); // 从 j 到 i 的最大高度
                f[i + 1] = min(f[i + 1], f[j] + max_h);
            }
        };
        
        return f[n]; // 翻译自 dfs(n-1)
    }
};
// @lc code=end
