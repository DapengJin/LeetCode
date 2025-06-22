#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 */

// @lc code=start
class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        int n = temperatures.size();
        vector<int> res(n);
        stack<int> s; // store the index of the temp

        // 从左到右
        // for (int i = 0; i < n ; i++)
        // {
        //     while (!s.empty() && temperatures[s.top()] < temperatures[i])
        //     {
        //         // found a warner date for s.top()
        //         res[s.top()] = i - s.top();
        //         s.pop();
        //     }

        //     s.push(i);
        // }

        // 从右到左
        for (int i = n - 1; i >= 0; i--)
        {
            while (!s.empty() && temperatures[i] >= temperatures[s.top()])
                s.pop();

            if (!s.empty())
                res[i] = s.top() - i;
            
            s.push(i); 
        }

        return res;
    }
};
// @lc code=end
