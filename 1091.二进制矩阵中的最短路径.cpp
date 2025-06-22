#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1091 lang=cpp
 *
 * [1091] 二进制矩阵中的最短路径
 */

// @lc code=start
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid[0][0] == 1) return -1;

        int m = grid.size(), n = grid[0].size();
        int dist = 0, count; 

        queue<pair<int,int>> q;
        q.push({0, 0}); 
        grid[0][0] = -1;
        count = q.size();

        while (count > 0)
        {
            dist ++;
            while (count --)
            {
                auto [r,c] = q.front(); 
                q.pop();

                if (r == m-1 && c == n-1) 
                {
                    return dist; 
                }

                for (int dx = -1; dx <=1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    { 
                        if (dx == 0 && dy == 0) continue;

                        int x = r + dx, y = c + dy; 

                        if (x < 0 || y < 0 || x>= m || y >= n || grid[x][y] != 0) continue;

                        grid[x][y] = -1; 
                        q.push({x, y}); 
                    }
                }
            }

            count = q.size(); 
        }

        return -1; 
    }
};
// @lc code=end

