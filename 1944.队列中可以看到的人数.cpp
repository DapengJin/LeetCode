#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1944 lang=cpp
 *
 * [1944] 队列中可以看到的人数
 */

// @lc code=start
class Solution
{
public:
    vector<int> canSeePersonsCount(vector<int> &heights)
    {
        int n = heights.size();
        stack<int> s;       // 单调栈，存放右侧尚未被阻挡的“人”的高度
        vector<int> res(n); // res[i] 存放 heights[i] 向右能看到的人数

        for (int i = n - 1; i >= 0; i--)
        {
            int h = heights[i], cnt = 0; // 当前 i 位置能看到的人数

            // 弹出所有比当前高度小的人，他们都会被 i 看到
            while (!s.empty() && h > s.top())
            {
                s.pop();
                cnt++;
            }

            // 如果栈不空，说明遇到了一个高度 ≥ h 的人
            // i 也能看到这一个，然后就被“挡”住，无法继续往更右看
            if (!s.empty())
                cnt++;

            res[i] = cnt; // 记录结果
            s.push(h);    // 把当前高度压入栈，作为左侧人可见的阻挡
        }

        return res;
    }
};
// @lc code=end
