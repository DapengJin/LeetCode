#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=901 lang=cpp
 *
 * [901] 股票价格跨度
 */

// @lc code=start
class StockSpanner
{
    stack<pair<int, int>> st;
    int cur_day = -1; // 第一个 next 调用算作第 0 天

public:
    StockSpanner()
    {
        st.emplace(-1, INT_MAX); // 这样无需判断栈为空的情况
    }

    int next(int price)
    {
        while (price >= st.top().second)
            st.pop(); // 栈顶数据后面不会再用到了，因为 price 更大

        int ans = ++cur_day - st.top().first;
        st.emplace(cur_day, price);
        return ans;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
// @lc code=end
