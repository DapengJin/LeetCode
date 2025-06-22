#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1453 lang=cpp
 *
 * [1453] 圆形靶内的最大飞镖数量
 */

// @lc code=start
// 定义点结构体，表示二维坐标
struct point
{
    double x, y;
    point(double i, double j) : x(i), y(j) {}
};

// 计算两点之间的欧几里得距离
double dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// 给定两个点 a、b 和半径 r，计算其中一个可能的圆心（圆心在 AB 垂直方向、到中点距离为 h）
point get_circle_center(point &a, point &b, int r)
{
    // 计算 AB 的中点
    point mid((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);

    // AB 距离的一半（即中点到任意端点的距离）
    double d = dist(a.x, a.y, mid.x, mid.y);

    // 若 AB 太长会导致 sqrt 为负，在外部判断保证 d <= r

    // 勾股定理求圆心到 AB 中点的垂直距离 h
    double h = sqrt(r * r - d * d);

    // 计算 AB 向量
    point ba(b.x - a.x, b.y - a.y);

    // 计算 AB 的垂直向量（顺时针旋转 90°）x1*x2 + y1*y2 = 0
    point hd(-ba.y, ba.x);

    // 单位化方向向量
    double len = sqrt(hd.x * hd.x + hd.y * hd.y);
    hd.x /= len;
    hd.y /= len;

    // 方向向量乘上距离 h，得到偏移量
    hd.x *= h;
    hd.y *= h;

    // 加上中点坐标，得到其中一个圆心（另一个方向是减）
    return point(hd.x + mid.x, hd.y + mid.y);
}

class Solution
{
public:
    int numPoints(vector<vector<int>> &points, int r)
    {
        int n = points.size();
        int ans = 0;

        // 枚举所有点对 (i, j)
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                // 情况 1：只考虑一个点作为圆心
                if (i == j)
                {
                    int cnt = 0;
                    for (int k = 0; k < n; k++)
                    {
                        double tmp = dist(points[i][0], points[i][1], points[k][0], points[k][1]);
                        if (tmp <= r + 1e-8)
                            cnt++; // 注意浮点误差
                    }
                    ans = max(cnt, ans);
                }

                // 情况 2：两个点构成直径的一部分
                else
                {
                    // 计算这两个点之间的距离
                    double d = dist(points[i][0], points[i][1], points[j][0], points[j][1]);

                    // 若两点间距超过直径，无法构成圆
                    if (d / 2 > r)
                        continue;

                    // 构造这两个点
                    point a(points[i][0], points[i][1]);
                    point b(points[j][0], points[j][1]);

                    // 计算其中一个方向的圆心，另一个方向在枚举 b->a 时会被自然处理
                    point res = get_circle_center(a, b, r);

                    // 统计以该圆心、半径为 r 的圆内包含的点数
                    int cnt = 0;
                    for (int k = 0; k < n; k++)
                    {
                        double tmp = dist(res.x, res.y, points[k][0], points[k][1]);
                        if (tmp <= r + 1e-8)
                            cnt++;
                    }
                    ans = max(cnt, ans);
                }
            }
        }
        return ans;
    }
};
// @lc code=end
