#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=730 lang=cpp
 *
 * [730] 统计不同回文子序列
 */

// @lc code=start
class Solution
{
public:
    const int MOD = 1e9 + 7; // 结果需要取模，防止溢出

    int countPalindromicSubsequences(string &s)
    {
        int n = s.size();

        // 定义 dp[k][i][j] 表示：在 s[i..j] 区间中，以字符 'a'+k 开头和结尾的回文子序列的个数
        vector<vector<vector<int>>> dp(4, vector<vector<int>>(n, vector<int>(n, 0)));

        // 初始化：长度为1的区间，只有当 s[i] == 'a'/'b'/'c'/'d' 时才算一个合法的回文
        for (int i = 0; i < n; i++)
        {
            dp[s[i] - 'a'][i][i] = 1;
        }

        // 枚举所有长度从2到n的子串
        for (int len = 2; len <= n; len++)
        {
            // 枚举子串的起点 i，终点 j = i + len - 1
            for (int i = 0, j = len - 1; j < n; i++, j++)
            {
                // 枚举字符 ch ∈ {'a', 'b', 'c', 'd'}，对应下标 k = 0 ~ 3
                for (char c = 'a', k = 0; c <= 'd'; c++, k++)
                {

                    // 情况1：s[i] == ch && s[j] == ch，说明我们可以构造形如 ch + (中间回文) + ch 的结构
                    if (s[i] == c && s[j] == c)
                    {
                        // 除了“ch”和“ch+ch”这两个，我们还可以从 s[i+1..j-1] 中找所有类型的回文包裹进来
                        dp[k][i][j] = (2LL +
                                       dp[0][i + 1][j - 1] +  // 例如 "bbbb" i,j = [0,3]。
                                       dp[1][i + 1][j - 1] +  //     dp['b'][1][2] = 2 分别是 b 和 bb
                                       dp[2][i + 1][j - 1] +  //     被 ch 夹住之后 变成了 bbb 和 bbbb
                                       dp[3][i + 1][j - 1]) % // 现在答案里 不包括 b 和 bb 了，所以要加上 2
                                      MOD;
                    }

                    // 情况2：s[i] == ch 但 s[j] != ch，说明只能考虑 s[i..j-1] 中以 ch 开头和结尾的回文
                    else if (s[i] == c)
                    {
                        dp[k][i][j] = dp[k][i][j - 1];
                    }

                    // 情况3：s[j] == ch 但 s[i] != ch，说明只能考虑 s[i+1..j] 中以 ch 开头和结尾的回文
                    else if (s[j] == c)
                    {
                        dp[k][i][j] = dp[k][i + 1][j];
                    }

                    // 情况4：s[i] != ch 且 s[j] != ch，跳过头尾两个字符，递归处理中间部分
                    else
                    {
                        dp[k][i][j] = dp[k][i + 1][j - 1];
                    }
                }
            }
        }

        // 最终答案：所有以 a/b/c/d 开头和结尾的回文子序列数量之和
        int res = 0;
        for (int i = 0; i < 4; i++)
        {
            res = (res + dp[i][0][n - 1]) % MOD;
        }
        return res;
    }
};
// @lc code=end

/**
 * follow up : 返回所有回文子序列
 *
 *      O(2^N) 涉及到子序列的 选/不选
 *
 */
class Solution1
{
    unordered_map<string, unordered_set<string>> memo;

public:
    int countPalindromicSubsequences(string s)
    {
        return helper(s).size();
    }

    unordered_set<string> helper(string s)
    {
        if (memo.contains(s))
            return memo[s];

        unordered_set<string> res;
        int n = s.size();
        if (s.size() <= 1)
            return {s};

        auto a = helper(s.substr(0, n - 1));
        res.insert(a.begin(), a.end());
        a = helper(s.substr(1, n - 1));
        res.insert(a.begin(), a.end());

        if (s[0] == s[n - 1])
        {
            unordered_set<string> subset = helper(s.substr(1, n - 2));
            string head = s.substr(0, 1);
            for (auto s1 : subset)
                res.insert(head + s1 + head);

            res.insert(head + head);
        }

        return memo[s] = res;
    }
};

class Solution
{
public:
    const int MOD = 1e9 + 7;

    int countPalindromicSubsequences(string s)
    {
        int n = s.size();

        // dp[i][j] 表示 s[i..j] 中不同的回文子序列数量
        vector<vector<int>> dp(n, vector<int>(n));

        // next[i][c] 表示从 i 开始往右，第一个字符 c ('a'~'d') 的下标位置
        // pre[i][c]  表示从 i 开始往左，第一个字符 c ('a'~'d') 的下标位置
        vector<vector<int>> next(n, vector<int>(4));
        vector<vector<int>> pre(n, vector<int>(4));

        // 初始化：所有单个字符自己构成一个回文
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = 1;
        }

        // 构建 pre 数组：从左到右记录每个字符上次出现的位置
        // 示例：s = "bccb"
        // i=0: pre[0][a]= -1, pre[0][b]=-1, pre[0][c]=-1, pre[0][d]=-1
        // i=1: pre[1][b]= 0, 其余 -1
        // i=2: pre[2][c]= 1, 其余看前面记录
        // i=3: pre[3][b]= 1, 其余看前面记录
        vector<int> pos(4, -1); // 初始化为 -1，表示未出现
        for (int i = 0; i < n; i++)
        {
            for (int c = 0; c < 4; c++)
            {
                pre[i][c] = pos[c];
            }
            pos[s[i] - 'a'] = i;
        }

        // 构建 next 数组：从右到左记录每个字符下次出现的位置
        // 示例：s = "bccb", n = 4
        // i=3: next[3][b]= 4, next[3][c]=4,...
        // i=2: next[2][c]=3
        // i=1: next[1][c]=2
        // i=0: next[0][b]=3
        pos = vector<int>(4, n); // 初始化为 n，表示之后没有出现
        for (int i = n - 1; i >= 0; i--)
        {
            for (int c = 0; c < 4; c++)
            {
                next[i][c] = pos[c];
            }
            pos[s[i] - 'a'] = i;
        }

        // 枚举区间长度，从 2 到 n
        for (int len = 2; len <= n; len++)
        {
            for (int i = 0; i + len <= n; i++)
            {
                int j = i + len - 1;

                // 情况一：s[i] == s[j]
                if (s[i] == s[j])
                {
                    int ch = s[i] - 'a';
                    int low = next[i][ch]; // 从 i 向右找到下一个 s[i] 的位置
                    int high = pre[j][ch]; // 从 j 向左找到上一个 s[j] 的位置

                    // 中间没有和 s[i] 相同的字符
                    if (low > high)
                    {
                        // 可以构造 2 个新的回文：s[i] 和 s[i] + s[j]
                        // 可以构造 子回文串个 ch+子回文串+ch
                        //      再加上原来已有的 子回文串个
                        dp[i][j] = (2 + dp[i + 1][j - 1] * 2) % MOD;
                    }

                    // 中间有一个和 s[i] 相同的字符
                    else if (low == high)
                    {
                        // 只能构造一个新的回文：s[i] + s[j]
                        // 可以构造 子回文串个 ch+子回文串+ch
                        //      再加上原来已有的 子回文串个
                        dp[i][j] = (1 + dp[i + 1][j - 1] * 2) % MOD;
                    }

                    // 中间有两个及以上和 s[i] 相同的字符
                    else
                    {
                        // 可以构造 子回文串个 ch+子回文串+ch
                        //      再加上原来已有的 子回文串个
                        // 要扣掉 low+1 到 high-1 中重复计算的部分
                        dp[i][j] = (0LL + dp[i + 1][j - 1] * 2 - dp[low + 1][high - 1] + MOD) % MOD;
                    }
                }
                // 情况二：s[i] != s[j]
                else
                {
                    // 所有来自左边区间和右边区间的回文子序列，加起来再减去重叠部分
                    dp[i][j] = (0LL + dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
                }
            }
        }

        return dp[0][n - 1];
    }
};