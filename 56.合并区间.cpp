#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=56 lang=cpp
 *
 * [56] 合并区间
 */

// @lc code=start

/**
 * follow up：
 *
 * A 和 B 都已经按 start 升序排好，
 *      那么我们可以用「归并排序」的思路将它们合并成一个有序列表，
 *      再对这个有序列表做一次线性扫描合并重叠区间。
 */
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> res;
        int n = intervals.size();

        sort(intervals.begin(), intervals.end());

        int s = intervals[0][0], e = intervals[0][1];

        for (int i = 1; i < n; i++)
        {
            int n_s = intervals[i][0], n_e = intervals[i][1];

            // overlap
            if (e >= n_s)
                e = max(e, n_e); // !!! case: n_e ∈ [s ,e]
            else
            {
                res.push_back({s, e});
                s = n_s;
                e = n_e;
            }
        }

        res.push_back({s, e});

        return res;
    }

    // Follow-up：合并两个已排序的 interval 列表
    vector<vector<int>> mergeTwoIntervalLists(
        vector<vector<int>> &A,
        vector<vector<int>> &B)
    {
        vector<vector<int>> merged_list;
        int m = A.size(), n = B.size();
        int i = 0, j = 0;

        while (i < m && j < n)
            if (A[i][0] < B[j][0])
                merged_list.push_back(A[i++]);
            else
                merged_list.push_back(B[j++]);

        while (i < m)
            merged_list.push_back(A[i++]);
        while (j < n)
            merged_list.push_back(B[j++]);

        return merge(merged_list);
    }
};
// @lc code=end
