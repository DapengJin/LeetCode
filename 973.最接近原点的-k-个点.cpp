#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=973 lang=cpp
 *
 * [973] 最接近原点的 K 个点
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
         // 最大堆，存放 pair<距离, 索引>
        priority_queue<pair<int, int>> q;
        int n = points.size();

        for (int i = 0; i < n; i++)
        {
            q.push({points[i][0] * points[i][0] + points[i][1] * points[i][1], i});

            if (q.size() > k) // !!! 不能放在 q.push() 之前，新元素还要入队比较大小才行。
                q.pop();
        }

        vector<vector<int>> res;

        while (q.size())
        {
            res.push_back(points[q.top().second]);
            q.pop();
        }

        return res;
    }
};
// @lc code=end
