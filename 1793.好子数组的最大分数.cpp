#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1793 lang=cpp
 *
 * [1793] 好子数组的最大分数
 */

// @lc code=start
class Solution {
public:
    int maximumScore(vector<int>& heights, int k) {
        heights.push_back(0); // 用 0 迫使 没有计算过的长方形出栈
        int n = heights.size(), res = 0;
        stack<pair<int, int>> s; // height, index
        s.emplace(INT_MIN, -1); // (INT_MIN, -1) 永不出栈

        for (int i = 0; i < n; i++)
        {
            int h = heights[i];

            // 遇到 h 比 栈顶元素 小
            // 那就说明 栈顶元素不能通过合并 h 来形成更大的长方形
            // 所以要算出栈顶长方形的面积，同时出栈
            while (!s.empty() && h <= s.top().first){

                auto [h_rec, ignore] = s.top();  // height of the rectangle
                s.pop(); 
                if (s.top().second < k && k < i) // don't include both i and top.second
                    res = max(res, h_rec *(i - s.top().second - 1)); 
            }

            s.emplace(h, i) ;
        }

        return res; 
    }
};
// @lc code=end

