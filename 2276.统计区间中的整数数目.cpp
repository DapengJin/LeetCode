#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2276 lang=cpp
 *
 * [2276] 统计区间中的整数数目
 */

// @lc code=start
class CountIntervals
{
    CountIntervals *left = nullptr, *right = nullptr;
    int l, r, cnt = 0;

public:
    CountIntervals() : l(1), r(1e9) {} // root

    CountIntervals(int l, int r) : l(l), r(r) {} // 动态开点 

    void add(int L, int R)
    {
        // 这个 node 已经满了
        if (cnt == r - l + 1) 
            return; 
        // 这个 node 完全包含在 add range 里面
        if (L <= l && r <= R) 
        {
            cnt = r - l + 1; // 更新 cnt 到满
            return; 
        }

        int mid = (l+r) / 2; 

        if (left == nullptr) left = new CountIntervals(l, mid);
        if (right == nullptr) right = new CountIntervals(mid+1, r); 

        if (L <= mid) left->add(L, R); // [L, mid]    L     到 mid
        if (R > mid) right->add(L, R); // [mid+1, R]  mid+1 到 R

        cnt = left->cnt + right->cnt; // !!! 记得 汇总左右树的 cnt
    }

    int count()
    {
        return cnt; 
    }
};

// @lc code=end

/* 珂朵莉树 */
class CountIntervals
{
    map<int, int> m; // {right : left}
    int cnt = 0;

public:
    CountIntervals()
    {
    }

    void add(int left, int right)
    {
        for (auto it = m.lower_bound(left);
             it != m.end() && it->second <= right;
             m.erase(it++))
        {
            int l = it->second, r = it->first;

            left = min(left, l);
            right = max(right, r);
            cnt -= r - l + 1;
        }

        cnt += right - left + 1;
        m[right] = left;
    }

    int count()
    {
        return cnt;
    }
};
