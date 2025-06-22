#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1209 lang=cpp
 *
 * [1209] 删除字符串中的所有相邻重复项 II
 */

// @lc code=start
class Solution
{
public:
    /**
     * 如果面试官没特别强调「大量重复块」或「性能极致优化」，
     *      优先写单字符入栈版。
     *          1. 代码简洁
     *          2. 可读性好
     *          3. 边界少
     *      写完后，再口头补充「其实还有块处理能减少 push/pop 次数」。
     */
    // 单字符入栈
    string removeDuplicates(string s, int k)
    {
        vector<pair<int, char>> counts;
        for (int i = 0; i < s.size(); ++i)
        {
            // 如果栈为空，或当前字符与栈顶字符不同，开启新计数
            if (counts.empty() || s[i] != counts.back().second)
                counts.push_back({1, s[i]});

            // 否则当前字符与栈顶字符相同，先将计数加1
            else if (++counts.back().first == k)
                // 如果计数恰好等于 k，则说明这 k 个字符应全部删除
                counts.pop_back();
        }

        // 重新构建结果字符串
        string res;
        for (auto &[cnt, c] : counts)
            res += string(cnt, c);

        return s;
    }
};
// @lc code=end
class Solution
{
public:
    // 整段连续处理
    string removeDuplicates(string s, int k)
    {
        vector<pair<char, int>> counts;
        int n = s.size(), i = 0;

        while (i < n)
        {
            int cnt = 1;
            i++;

            // 向后扫描相同字符，直到遇到不同字符或结束
            while (i < n && s[i] == s[i - 1])
            {
                i++;
                cnt++;
            }

            if (counts.empty() || counts.back().first != s[i - 1])
            {
                cnt %= k;
                // 只有剩余 cnt>0 时才需要压入
                if (cnt != 0)
                    counts.push_back({s[i - 1], cnt});
            }
            else
            {
                // 否则需要把当前块和栈顶块合并
                int left = (cnt + counts.back().second) % k;

                // 刚好被删除完，就弹出栈顶
                if (left == 0)
                    counts.pop_back();
                // 否则更新栈顶剩余次数
                else
                    counts.back().second = left;
            }
        }

        // 根据栈中剩余的 (char, count) 重建结果字符串
        s = "";
        for (auto [c, cnt] : counts)
            s += string(cnt, c);

        return s;
    }
};