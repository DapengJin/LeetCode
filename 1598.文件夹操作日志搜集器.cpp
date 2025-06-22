#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1598 lang=cpp
 *
 * [1598] 文件夹操作日志搜集器
 * 
 * 和 71 一样
 */

// @lc code=start
class Solution {
public:
    int minOperations(vector<string>& logs) {
        stack<string> st;

        for (auto &log: logs)
        { 
            if (log == "./")
                continue;
            else if (log != "../")
                st.push(log); 
            else if (st.size())
                st.pop(); 
        }

        return st.size();
    }
};
// @lc code=end

