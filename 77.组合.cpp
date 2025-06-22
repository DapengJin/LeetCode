#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<int> path;
        vector<vector<int>> res;

        /* 选/不选 */
        function<void(int)> dfs = [&](int idx)
        {
            if (path.size() == k)
            {
                res.push_back(path);
                return;
            }

            if (idx == n + 1) // !!! 不包括 0
                return;

            dfs(idx + 1);

            path.push_back(idx);
            dfs(idx + 1);
            path.pop_back();
        };

        dfs(1); // !!! 不包括 0

        /* 选第几个 */
        // function<void(int)> dfs = [&](int idx)
        // {
        //     int left = k - path.size();

        //     // if (idx < left) return; // not enough elements to choose

        //     if (path.size() == k)
        //     {
        //         res.push_back(path);
        //         return;
        //     }

        //     // j > left - 1 意思是 选了 j 之后，至少 还要有 left - 1 个数可以选
        //     for (int j = idx; j > left - 1; j--)
        //     {
        //         path.push_back(j);
        //         dfs(j - 1);
        //         path.pop_back();
        //     }
        // };

        // dfs(n);

        return res;
    }
};
// @lc code=end
class Solution1
{
public:
    void bt(vector<vector<int>> &res, vector<int> &cmb, int pos, int k, int n)
    {
        if (cmb.size() == k)
        {
            res.push_back(cmb);
            return;
        }

        for (int i = pos; i <= n; i++)
        {
            cmb.push_back(i);
            // !!! bt(res, cmb, i   + 1, k, n);
            // not bt(res, cmb, pos + 1, k, n);
            bt(res, cmb, i + 1, k, n);
            cmb.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> res;
        vector<int> cmb;

        bt(res, cmb, 1, k, n);

        return res;
    }
};