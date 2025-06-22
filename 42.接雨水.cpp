#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size(), res = 0;

        /* 双指针 */

        int l = 0, lmax = height[l], r = n - 1, rmax = height[r];

        // while (l < r) // 不用 <=, 因为停止点是最高点
        // {
        //     if (lmax > rmax)
        //     {
        //         r--; 
        //         res += max(0, rmax - height[r]); 
        //         rmax = max(rmax, height[r]);
        //     }
        //     else
        //     { 
        //         l++; 
        //         res += max(0, lmax - height[l]); 
        //         lmax = max(lmax, height[l]);
        //     }
        // }

        while (l < r) // 不用 <=, 因为停止点是最高点
        {
            lmax = max(lmax, height[l]); 
            rmax = max(rmax, height[r]); 

            if (lmax > rmax){ 
                res += rmax - height[r]; 
                r--; 
            }
            else { 
                res += lmax -height[l]; 
                l++; 
            }
        }

        return res; 

        /* 单调栈 */

        // stack<int> s; // store the index

        // for (int i = 0; i < n; i++)
        // {
        //     // 下降的，装不了水，只有上升的才能装水
        //     while (!s.empty() && height[s.top()] <= height[i])
        //     {
        //         int bottom_height = height[s.top()];
        //         s.pop();

        //         // 一个桶需要两个边和一个底
        //         if (!s.empty())
        //             res +=  (  min(height[s.top()], height[i]) // 找到最低那块板的高度
        //                      - bottom_height
        //                     ) 
        //                    *
        //                     (i - s.top() - 1); // 宽度
        //     }

        //     s.push(i);
        // }

        // return res;
    }
};
// @lc code=end
