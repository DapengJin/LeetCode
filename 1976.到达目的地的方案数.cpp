#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1976 lang=cpp
 *
 * [1976] 到达目的地的方案数
 */

// @lc code=start
class Solution
{
public:
    int countPaths(int n, vector<vector<int>> &roads)
    {
        // init aj
        int m = roads.size();
        vector<vector<pair<int, int>>> aj(n);

        for (auto &r : roads)
        {
            int x = r[0], y = r[1], d = r[2];
            aj[x].push_back({y, d});
            aj[y].push_back({x, d});
        }
        // dis && f ++ init
        vector<long long> dis(n, LLONG_MAX), f(n, 0);
        dis[0] = 0;
        f[0] = 1;

        // pq {distance, idx}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            auto [dis_node, node] = pq.top();
            pq.pop();

            if (node == n - 1)
                return f[n - 1];

            if (dis_node > dis[node]) // ← lazy delete：如果取出的路径不是最短的，跳过（过期）
                continue;

            // dis child || add child
            for (auto c : aj[node])
            {
                auto [child, dis_child] = c;

                long long cur_child_dis = dis[node] + dis_child;

                // 如果找到更短的路径，更新距离和路径数，并加入队列
                if (dis[child] > cur_child_dis)
                {
                    f[child] = f[node];
                    dis[child] = cur_child_dis;
                    pq.push({cur_child_dis, child}); // ← lazy relax：不删旧的，直接加新值
                }
                // 如果找到一条等长的最短路径，累加路径数
                else if (dis[child] == cur_child_dis)
                {
                    f[child] = (f[child] + f[node]) % 1'000'000'007;
                }
            }
        }

        return -1;
    }
};
// @lc code=end
