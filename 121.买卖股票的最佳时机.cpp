#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int lowest = INT_MAX, profit = 0; 

        for (auto price: prices) 
        { 
            
            lowest = min(lowest, price); 
            profit = max(profit, price - lowest); 
        }
        
        return profit; 
    }
};
// @lc code=end

