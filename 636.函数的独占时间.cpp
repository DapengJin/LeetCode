#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=636 lang=cpp
 *
 * [636] 函数的独占时间
 */

// @lc code=start
class Solution
{
public:
    vector<int> exclusiveTime(int n, vector<string> &logs)
    {
        vector<int> res(n, 0);    // 记录每个函数的独占执行时间
        stack<pair<int, int>> st; // 维护一个栈，存储 (函数编号, 开始时间)

        for (auto log : logs)
        {
            char type[10]; // 存储 "start" 或 "end"
            int idx, timestamp;
            sscanf(log.c_str(), "%d:%[^:]:%d", &idx, type, &timestamp);

            if (type[0] == 's') // 处理 "start" 事件
            {
                if (!st.empty()) // 若栈不为空，把已经执行的时间加到 res
                    res[st.top().first] += timestamp - st.top().second;

                st.push({idx, timestamp});
            }
            else // 处理 "end" 事件
            {
                res[idx] += timestamp - st.top().second + 1; // 计算当前函数的独占时间
                st.pop();

                if (!st.empty()) // 若栈不为空，更新新的栈顶函数的开始时间（之前的时间已经存过了
                    st.top().second = timestamp + 1;
            }
        }

        return res;
    }
};
// @lc code=end
