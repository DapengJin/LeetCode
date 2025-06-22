#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2266 lang=cpp
 *
 * [2266] 统计打字方案数
 */

// @lc code=start
const int MOD = 1000'000'007;
const int MX = 100001;

// f[i] 表示长为 i 的只有一种字符的字符串所对应的文字信息种类数
long long f[MX], // 按键最多表示 3 个字母的
    g[MX];       // 按键最多表示 4 个字母的 '7' 和 '9'

int init = []()
{
    f[0] = g[0] = 1;
    f[1] = g[1] = 1;
    f[2] = g[2] = 2;
    f[3] = g[3] = 4;

    for (int i = 4; i < MX; i++)
    {
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % MOD;
        g[i] = (g[i - 1] + g[i - 2] + g[i - 3] + g[i - 4]) % MOD;
    }

    return 0;
}();
class Solution
{
public:
    int countTexts(string s)
    {

        int n = s.size();
        long long res = 1;
        int cnt = 0;

        for (int i = 0; i < n; i++)
        {

            cnt++;

            if (i == s.size() - 1 || // 最后一个
                s[i] != s[i + 1])    // 不是最后一个 && 和 后面 一个不同
            {
                char c = s[i];

                res = (res * ((c == '7' || c == '9') ? g[cnt] : f[cnt])) % MOD;
                cnt = 0; // reset counter
            }
        }

        return res; 

        /* dfs + memorizition */
        /**
         * 爬楼梯，有可能爬 1-4 层
         */
        // vector<int> memo(n+1, -1);

        // // i 是字符串长度
        // // return 总结果数
        // function<int(int)> dfs = [&](int i) -> int
        // {
        //     if (i == 0)
        //         return 1; // 长度为 0，只有一种

        //     if (memo[i] != -1) return memo[i];

        //     char c = s[i - 1];
        //     int sum = 0;
        //     int m = (c == '7' || c == '9') ? 4 : 3;  // 向上爬的层数

        //     for (int j = 1; j <= m &&                // 最多 m 次
        //                     i >= j &&                // 不要溢出
        //                     s[i - j] == c; // 是重复的字母
        //          j++)
        //     {
        //         sum = (sum + dfs(i - j)) % MOD;
        //     }

        //     memo[i] = sum;
        //     return sum;
        // };

        // return dfs(n);
    }
};
// @lc code=end
