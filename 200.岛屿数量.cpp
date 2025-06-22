#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 */

// @lc code=start
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        function<void(int, int)> dfs = [&](int i, int j)
        {
            if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1')
                return;

            grid[i][j] = '2';

            dfs(i + 1, j);
            dfs(i, j + 1);
            dfs(i - 1, j);
            dfs(i, j - 1);
        };

        int count = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1')
                {
                    count++;
                    dfs(i, j);
                }
            }

        return count;
    }
};
// @lc code=end
class Solution1
{
public:
    // 自定义哈希函数
    struct pair_hash
    {
        size_t operator()(const pair<int, int> &p) const
        {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

    int numIslands(vector<vector<char>> &grid)
    {
        unordered_map<pair<int, int>, pair<int, int>, pair_hash> parent;
        int m = grid.size(), n = grid[0].size();
        int dir[5] = {1, 0, -1, 0, 1};
        int count = 0;
        function<pair<int, int>(pair<int, int>)> find_ =
            [&](pair<int, int> child) -> pair<int, int>
        {
            if (child == parent[child])
                return child;

            parent[child] = find_(parent[child]);
            return parent[child];
        };

        auto union_ = [&](pair<int, int> a, pair<int, int> b)
        {
            auto pa = find_(parent[a]);
            auto pb = find_(parent[b]);

            if (pa != pb)
            {
                parent[pa] = pb;
                count--;
            }
        };

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '0')
                    continue;

                parent[{i, j}] = {i, j};
                count++;

                for (int d = 0; d < 4; d++)
                {
                    int ni = i + dir[d], nj = j + dir[d + 1];

                    if (ni < 0 || ni >= m || nj < 0 || nj >= n)
                        continue;

                    if (parent.contains({ni, nj}))
                        union_({i, j}, {ni, nj});
                }
            }

        return count;
    }
};