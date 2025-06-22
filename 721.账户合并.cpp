#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=721 lang=cpp
 *
 * [721] 账户合并
 */

// @lc code=start
class Solution
{
public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        int n = accounts.size();

        // {email: [idx1, idx2, ...]}
        unordered_map<string, vector<int>> email2idx;
        for (int i = 0; i < n; i++)
            for (int k = 1; k < accounts[i].size(); k++)
                email2idx[accounts[i][k]].push_back(i);

        unordered_set<string> email_set;  // 用于收集 DFS 中访问到的邮箱地址
        vector<int> vis(accounts.size()); // 标记哪些账户已经被访问过

        function<void(int)> dfs = [&](int i) -> void
        {
            vis[i] = true;

            // 遍历 i 的所有邮箱地址
            for (int k = 1; k < accounts[i].size(); k++)
            {
                string &email = accounts[i][k];

                // 如果这个邮箱已经加到集合中，说明已经处理过
                if (email_set.contains(email)) continue;

                email_set.insert(email);
                for (int j : email2idx[email]) // 遍历所有包含该邮箱地址的账户下标 j
                    if (!vis[j]) dfs(j);       // j 没有访问过
                      
            }
        };

        vector<vector<string>> ans;
        for (int i = 0; i < vis.size(); i++)
        {
            if (vis[i]) continue;

            email_set.clear();
            dfs(i);

            // 收集结果：先放用户名，再放所有搜到的邮箱，最后排序
            vector<string> res = {accounts[i][0]};
            res.insert(res.end(), email_set.begin(), email_set.end());
            sort(res.begin() + 1, res.end());

            ans.push_back(move(res));
        }
        return ans;
    }
};
// @lc code=end
