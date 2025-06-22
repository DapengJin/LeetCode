#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2397 lang=cpp
 *
 * [2397] 被列覆盖的最多行数
 */

// @lc code=start
class Solution
{
public:
    int maximumRows(vector<vector<int>> &matrix, int numSelect)
    {
        int m = matrix.size(), n = matrix[0].size();
        unordered_set<int> path; // idx
        int res = 0;

        function<void(int)> dfs = [&](int i)
        {
            if (path.size() == numSelect )
            {
                int s = m;

                // check how many rows are covered
                for (int x = 0; x < m; x++)
                {
                    for (int y = 0; y < n; y++)
                    {
                        if (!path.contains(y) && matrix[x][y] == 1)
                        {
                            s--;
                            break;
                        }
                    }
                }

                res = max(res, s); 

                return;
            }

            if (i == n) return; // !!! 不加就死循环，不能加在前面

            dfs(i+1); 
            
            path.insert(i); 
            dfs(i+1); 
            path.erase(i); 
        };

        dfs(0); 

        return res; 
    }
};
// @lc code=end
