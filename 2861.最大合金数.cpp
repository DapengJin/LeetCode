#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2861 lang=cpp
 *
 * [2861] 最大合金数
 */

// @lc code=start
class Solution
{
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>> &composition, vector<int> &stock, vector<int> &cost)
    {
        // 单调性 （钱越多可以制造的合金越多）
        int res = 0;
        // 答案范围的最大值是：假设
        //      1. 只需 一种金属
        //      2. 每次制造合金 这种金属之需要 1 个
        //      3. 这种金属的 cost 为 1
        int mx = ranges::max(stock) + budget;

        for (auto c : composition)
        {
            auto check = [&](long long mid) -> bool // mid * c[i] 可能溢出
            {
                // 计算 造出 mid 数量的合金 所需的 budget
                long long sum = 0;

                for (int i = 0; i < n; i++)
                {
                    // !!! stock 不够用了
                    if (stock[i] < mid * c[i])
                    {
                        // 需要花钱
                        sum += max(mid * c[i] - stock[i], 0LL) * cost[i];

                        if (sum > budget)
                            return false;
                    }
                }

                return true;
            };

            // 二分下界：可以设为 1。更巧妙的做法是，设当前答案为 ans，
            // 那么可以初始化二分下界为 ans+1，因为算出小于等于 ans 的值是没有意义的，不会让 ans 变大。
            // 如果这台机器无法制造出至少 ans+1 份合金，那么二分循环结束后的结果为 ans，不影响答案。
            int l = res, r = mx + 1;

            while (l + 1 < r) 
            { 
                int mid = l + (r - l)  /2 ; 

                (check(mid) ? l : r) = mid; 
            }

            res = l; 
        }

        return res; 
    }
};
// @lc code=end
