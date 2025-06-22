#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=54 lang=cpp
 *
 * [54] 螺旋矩阵
 */

// @lc code=start
/*
 * LeetCode 54 — Spiral Matrix
 *
 * 思路：
 *  - 使用方向数组 dir，使 (dir[d], dir[d+1]) 表示在 d 方位上的行增量和列增量：
 *      d = 0 → 向右  (0, 1)
 *      d = 1 → 向下  (1, 0)
 *      d = 2 → 向左  (0, -1)
 *      d = 3 → 向上 (-1, 0)
 *    通过对 d 取模 (d + 1) % 4 在四个方向之间循环。
 *
 *  - 用变量 m 表示当前剩余的“行数高度”，n 表示当前剩余的“列数宽度”。
 *    每完成一条边的遍历后，就将对应的边长度减一（m--），
 *    再将 m、n 交换，使下次循环遍历另一维度。
 *    这种技巧可以简洁地模拟螺旋收缩边界。
 *
 *  - 由于遍历从坐标 (0,0) 的左上角“外侧”开始，
 *    初始列索引 j 设为 -1，让第一次向右移动时到达 (0,0)。
 */
class Solution
{
    // dir 数组：四个方向的行/列增量，配合偏移量索引 (d, d+1)
    int dir[5] = {0, 1, 0, -1, 0};

public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size();    // m: 剩余行数
        int n = matrix[0].size(); // n: 剩余列数
        const int total = m * n;  // 总元素数量
        vector<int> res;

        int i = 0, j = -1; // 从 (0,-1) 出发，让第一次向右到 (0,0)

        // d 表示当前方向索引；当 res.size() == total 时结束
        for (int d = 0; res.size() < total; d = (d + 1) % 4)
        {
            // 当前边的长度是 n（先走列数），遍历 n 个元素
            for (int k = 0; k < n; ++k)
            {
                i += dir[d];     // 行坐标按当前方向增量更新
                j += dir[d + 1]; // 列坐标按当前方向增量更新
                res.push_back(matrix[i][j]);
            }

            // 完成一条边后：
            //   1. 缩小边界（对下一条边而言行数少 1）
            //   2. m、n 交换，使下一循环遍历另一维（先走行、再走列之间互换）
            --m;
            swap(m, n);
        }
        return res;
    }
};
// @lc code=end

class Solution1
{
    static constexpr int DIRS[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 右下左上
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size(); // m 行 n 列
        vector<int> ans(m * n);                      // 结果数组，容量为矩阵元素总数

        int i = 0, j = 0, d = 0; // 起点 (0,0)，方向索引 d=0 表示初始向右

        for (int k = 0; k < m * n; ++k)
        {
            ans[k] = matrix[i][j];  // 当前元素加入结果数组
            matrix[i][j] = INT_MAX; // 标记当前单元格为访问过（用特殊值 INT_MAX）

            // 计算下一步的位置
            int x = i + DIRS[d][0];
            int y = j + DIRS[d][1];

            // 若下一步越界或已经访问过，右转（顺时针旋转方向）
            if (x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] == INT_MAX)
                d = (d + 1) % 4;

            // 向当前方向走一步
            i += DIRS[d][0];
            j += DIRS[d][1];
        }

        return ans;
    }
};
