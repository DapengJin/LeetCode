#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=498 lang=cpp
 *
 * [498] 对角线遍历
 */

// @lc code=start
class Solution
{
public:
    /**
     * 总原则：
     * 
     *  设当前遍历的是第 i 条对角线（从上到下编号，第 0 条是最上面那条）
     * 
     *      •	总共 m + n - 1 条对角线（因为矩阵左上到右下跨度是这么多）
     *      •	当前编号为 i 的对角线上，所有 (x, y) 坐标满足：x + y == i
     */
    vector<int> findDiagonalOrder(vector<vector<int>> &mat)
    {
        int m = mat.size();    // 行数
        int n = mat[0].size(); // 列数
        vector<int> res;

        // 总共会有 m + n - 1 条对角线（从上到下编号）
        for (int i = 0; i < m + n - 1; i++)
        {
            // 偶数编号对角线：从下往上走
            if (i % 2 == 0)
            {
                int x = min(i, m - 1); // 起始行（最多为 m-1）
                int y = i - x;         // 起始列
                while (x >= 0 && y < n)
                {
                    res.push_back(mat[x][y]);
                    x--;
                    y++;
                }
            }
            // 奇数编号对角线：从上往下走
            else
            {
                int y = min(i, n - 1); // 起始列（最多为 n-1）
                int x = i - y;         // 起始行
                while (x < m && y >= 0)
                {
                    res.push_back(mat[x][y]);
                    x++;
                    y--;
                }
            }
        }

        return res;
    }
};
// @lc code=end
