#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=71 lang=cpp
 *
 * [71] 简化路径
 */

// @lc code=start
class Solution
{
public:
    string simplifyPath(string path)
    {
        vector<string> stk;
        istringstream ss(path);
        string s;

        while (getline(ss, s, '/'))
            if (s.empty() || s == ".") // 空串或当前目录 '.'，跳过
                continue;
            else if (s != "..") // 普通目录名，加入栈中
                stk.push_back(s);
            else if (!stk.empty()) // 遇到 ".." 且栈不空，返回上一级目录
                stk.pop_back();

        // 构造结果路径
        string ans;

        for (string &s : stk)
            ans += '/' + s;

        return stk.empty() ? "/" : ans; // 空栈返回根目录 "/"
    }
};
// @lc code=end
