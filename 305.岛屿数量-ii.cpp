#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=305 lang=cpp
 *
 * [305] 岛屿数量 II
 */

// @lc code=start
// 自定义哈希函数
struct pair_hash
{
    size_t operator()(const pair<int, int> &p) const
    {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
class Solution
{
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>> &positions)
    {
        unordered_map<pair<int, int>, pair<int, int>, pair_hash> parent;

        function<pair<int, int>(pair<int, int>)> find_ = [&](pair<int, int> a)
        {
            if (parent[a] == a)
                return a;

            parent[a] = find_(parent[a]);

            return parent[a];
        };

        auto union_ = [&](pair<int, int> a, pair<int, int> b)
        {
            int res = 0;
            auto pa = find_(a);
            auto pb = find_(b);

            if (pa != pb)
                res = -1;

            parent[pa] = pb;

            return res;
        };

        int cnt = 0;
        vector dir{-1, 0, 1, 0, -1};
        vector<int> res;

        for (int i = 0; i < positions.size(); i++)
        {
            int x = positions[i][0], y = positions[i][1];
            pair<int, int> node{x, y};

            if (!parent.contains(node))
            {

                cnt++;
                parent[node] = node;

                for (int j = 0; j < 4; j++)
                {
                    int nx = x + dir[j], ny = y + dir[j + 1];
                    pair<int, int> n_node{nx, ny};

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        continue;

                    if (parent.contains(n_node))
                    {
                        cnt += union_(node, n_node);
                    }
                }
            }

            res.push_back(cnt);
        }

        return res;
    }
};
// @lc code=end