#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=301 lang=cpp
 *
 * [301] 删除无效的括号
 */

// @lc code=start
class Solution
{
public:
    vector<string> removeInvalidParentheses(string s)
    {
        int n = s.size();
        unordered_set<string> res;
        int res_len = 0;

        // dfs(i, expr, score)
        function<void(int, string, int)> dfs = [&](int i, string expr, int score)
        {
            // stop i == n || score < 0
            if (score < 0)
                return;

            if (i == n)
            {
                if (score == 0 && expr.size() >= res_len)
                {
                    if (expr.size() > res_len)
                        res.clear();

                    res_len = expr.size();
                    res.insert(expr);
                }

                return;
            }

            char c = s[i];

            if (c == '(')
            {
                // 不选
                dfs(i + 1, expr, score);
                // 选
                dfs(i + 1, expr + c, score + 1);
            }
            else if (c == ')')
            {
                // 不选
                dfs(i + 1, expr, score);
                // 选
                dfs(i + 1, expr + c, score - 1);
            }
            else
            {
                // 选
                dfs(i + 1, expr + c, score);
            }
        };

        dfs(0, "", 0);

        return vector<string>(res.begin(), res.end());
    }
};
// @lc code=end
class Solution1
{
public:
    vector<string> res;
    vector<string> removeInvalidParentheses(string s)
    {
        int lremove = 0;
        int rremove = 0;

        for (char c : s)
        {
            if (c == '(')
            {
                lremove++;
            }
            else if (c == ')')
            {
                if (lremove == 0)
                {
                    rremove++;
                }
                else
                {
                    lremove--;
                }
            }
        }
        helper(s, 0, lremove, rremove);
        return res;
    }

    void helper(string str, int start, int lremove, int rremove)
    {
        if (lremove == 0 && rremove == 0)
        {
            if (isValid(str))
            {
                res.push_back(str);
            }
            return;
        }
        for (int i = start; i < str.size(); i++)
        {
            if (i != start && str[i] == str[i - 1])
            {
                continue;
            }
            // 如果剩余的字符无法满足去掉的数量要求，直接返回
            if (lremove + rremove > str.size() - i)
            {
                return;
            }
            // 尝试去掉一个左括号
            if (lremove > 0 && str[i] == '(')
            {
                helper(str.substr(0, i) + str.substr(i + 1), i, lremove - 1, rremove);
            }
            // 尝试去掉一个右括号
            if (rremove > 0 && str[i] == ')')
            {
                helper(str.substr(0, i) + str.substr(i + 1), i, lremove, rremove - 1);
            }
        }
    }

    inline bool isValid(const string &str)
    {
        int cnt = 0;

        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '(')
            {
                cnt++;
            }
            else if (str[i] == ')')
            {
                cnt--;
                if (cnt < 0)
                {
                    return false;
                }
            }
        }

        return cnt == 0;
    }
};