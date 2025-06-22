#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 */

// @lc code=start

// 拓扑排序 Topological ordering
class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        int n = numCourses;
        vector aj(n, vector<int>());
        vector<int> indegree(n, 0); // !!! 入度表

        for (auto e : prerequisites)
        {
            int u = e[1], v = e[0];

            aj[u].push_back(v); // u -> v 表示 u 是 v 的前置课程
            indegree[v]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 0) // 入度为 0 的课程可以学
                q.push(i);

        vector<int> res;

        while (q.size())
        {
            int len = q.size();
            int node = q.front();
            q.pop();

            res.push_back(node);

            for (auto child : aj[node]) // 更新它所指向的课程的 indegree
            {
                indegree[child]--;

                if (indegree[child] == 0)
                    q.push(child);
            }
        }
        // 如果学完了所有课程就返回顺序，否则返回空数组
        return res.size() == n ? res : vector<int>();
    }
};
// @lc code=end
