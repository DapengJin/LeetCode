#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=946 lang=cpp
 *
 * [946] 验证栈序列
 */

// @lc code=start
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int m = pushed.size(), n = popped.size(); 
        int j = 0; 
        stack<int> st; 

        for (int i = 0; i < m ; i++)
        { 
            st.push(pushed[i]); // 入栈

            // 如果 栈顶 和 popped[j] 相同 就出栈 
            while (j < n && !st.empty() && st.top() == popped[j])
            { 
                st.pop(); 
                j++; // 记得 ++
            }
        }

        return st.empty(); 
    }
};
// @lc code=end

