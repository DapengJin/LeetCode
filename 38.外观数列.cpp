#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=38 lang=cpp
 *
 * [38] 外观数列
 */

// @lc code=start
class Solution
{
public:
    string countAndSay(int n)
    {
        function<string(int)> dfs = [&](int i) -> string
        {
            if (i == 1)
                return "1";

            string prev = dfs(i - 1);
            string res;

            int cnt = 1;

            for (int j = 1; j < prev.size(); j++)
            {
                if (prev[j] == prev[j - 1])
                {
                    cnt++;
                }
                else
                {
                    res += to_string(cnt); // 先说数量
                    res += prev[j - 1];    // 再说字符
                    cnt = 1;               // 重置计数器
                }
            }

            // 最后一组也要处理
            res += to_string(cnt);
            res += prev.back();

            return res;
        };

        return dfs(n);
    }
};
// @lc code=end
class Solution1
{
public:
    string countAndSay(int n)
    {
        string res = "1"; // 初始 n = 1 时的字符串

        for (int i = 2; i <= n; i++)
        {
            string next; // 构建下一个字符串
            int cnt = 1; // 当前字符数量统计

            for (int j = 1; j < res.size(); j++)
            {
                if (res[j] == res[j - 1])
                {
                    cnt++; // 相同字符累加
                }
                else
                {
                    // 遇到不同字符，输出上一组
                    next += to_string(cnt); // 数量
                    next += res[j - 1];     // 字符
                    cnt = 1;                // 重置计数器
                }
            }

            // 最后一组字符也要加入
            next += to_string(cnt);
            next += res.back();

            res = next; // 更新结果
        }

        return res;
    }
};