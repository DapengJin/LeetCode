#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2014 lang=cpp
 *
 * [2014] 重复 K 次的最长子序列
 */

// @lc code=start
class Solution
{
public:
    string longestSubsequenceRepeatedK(string s, int k)
    {
        // n < k * 8 ：答案的最大长度为 7
        int n = s.length();

        // 预处理：nxt[i][c] 表示从 s[i] 出发，下一个字符 c 出现的位置
        vector<vector<int>> nxt(n + 1);
        vector<int> pos(26, n + 1); // 初始化每个字符的下标为越界值 n+1
        for (int i = n; ~i; --i)
        {
            nxt[i] = pos; // 记录当前 pos 状态到 nxt[i]
            if (i)
                pos[s[i - 1] - 'a'] = i; // 从后往前更新字符出现的位置
        }

        // 检查某个字符串 p 能否作为 s 的子序列重复 k 次
        auto check = [&](string p)
        {
            int i = 0;
            for (int cnt = 0; cnt < k; ++cnt)
            {
                for (int j = 0; j < p.length(); ++j)
                {
                    i = nxt[i][p[j] - 'a']; // 使用预处理表找下一个匹配字符位置
                    if (i == n + 1)         // 匹配失败
                        return false;
                }
            }
            return true;
        };

        // ans[len] 存储所有长度为 len 的可行子序列
        vector<string> ans[8];
        ans[0].push_back("");

        // 枚举长度从 1 到 7 的所有可能子序列（因题目中 s.length() < 8*k）
        for (int len = 1; len < 8; ++len)
        {
            for (auto &t : ans[len - 1]) // 在所有上一步的结果基础上扩展
            {
                for (char c = 'a'; c <= 'z'; ++c)
                {
                    string p = t + c; // 尝试添加一个新字符
                    if (check(p))     // 如果这个新串 p 合法，就加入下一级
                        ans[len].push_back(p);
                }
            }
        }

        // 从长到短遍历，返回字典序最大的可行解
        for (int i = 7; ~i; --i)
        {
            if (ans[i].size() == 0)
                continue;
            return ans[i].back(); // 由于遍历时 c 从小到大，back 是字典序最大的
        }

        return "";
    }
};
// @lc code=end
