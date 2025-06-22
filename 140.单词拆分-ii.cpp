#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=140 lang=cpp
 *
 * [140] 单词拆分 II
 */
class Solution
{
public:
    /**
     * memo
     * 
     * 时间复杂度
     *      最坏情况下，如果 s = "aaaaaaa" 
     *                    wordDict = ["a", "aa", "aaa", "aaaa"]，
     *      显然，s 的任意一种分隔方法均符合题目要求。这一部分的占用的空间至少为 O(n⋅2ⁿ)，
     *      其中 n 是 s 的长度
     *      即，s 的分隔方法有 2ⁿ 种，每一种方法需要一个长度为 O(n) 的字符串进行存储。
     * 
     * 空间复杂度
     *      (n (字符串长度) * 2ⁿ (存储所有可能的拆分))
     */
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo; // 记忆化存储 s[i:n] 的拆分结果

        function<vector<string>(int)> dfs = [&](int i) -> vector<string>
        {
            if (memo.count(i))
                return memo[i]; // 记忆化搜索
            if (i == s.size())
                return {""}; // 递归终止：空字符串情况

            vector<string> res;
            for (int j = i; j < s.size(); ++j)
            {
                string sub = s.substr(i, j - i + 1);
                if (wordSet.count(sub))
                {
                    vector<string> nextWords = dfs(j + 1);
                    for (const string &next : nextWords)
                    {
                        res.push_back(sub + (next.empty() ? "" : " " + next));
                    }
                }
            }
            return memo[i] = res; // 记忆化存储当前 i 位置的计算结果
        };

        return dfs(0);
    }
};
// @lc code=start

// @lc code=end

/* back tracking */
class Solution1
{
public:
    /**
     * 时间复杂度
     *      最坏情况下，如果 s = "aaaaaaa" 且 wordDict = ["a", "aa", "aaa", "aaaa"]，递归的分支可能会形成一个类似二叉树的结构，导致 O(2ⁿ) 的复杂度。
     *      平均情况下，由于 unordered_set 查询是 O(1)，所以对 wordDict 进行 contains(sub) 检查不会增加复杂度。
     *
     *  最终时间复杂度： O(nⁿ * n)
     *      O(nⁿ) 是递归分支的数量（指数级）。
     *      O(n) 是 substr() 的代价。
     *
     * 空间复杂度
     *      (n (字符串长度) * 2^n (存储所有可能的拆分))
     */
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> word_set(wordDict.begin(), wordDict.end());
        vector<string> res; // (n (字符串长度) * 2^n (存储所有可能的拆分))
        int n = s.size();

        function<void(string, int)> dfs = [&](string expr, int i)
        {
            if (i == n)
            {
                res.push_back(expr);
                return;
            }

            for (int j = i; j < n; j++)
            {
                auto sub = s.substr(i, j - i + 1);

                if (word_set.contains(sub))
                    if (i == 0)
                        dfs(sub, j + 1);
                    else
                        dfs(expr + " " + sub, j + 1);
            }
        };

        dfs("", 0);

        return res;
    }
};