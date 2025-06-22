#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=135 lang=cpp
 *
 * [135] 分发糖果
 */

// @lc code=start
class Solution {
public:
    int candy(vector<int>& ratings) {
        // res init 1
        int n = ratings.size(); 
        vector<int> res(n, 1); 

        // from right to left,if cur rating > prev rating, cur = prev + 1
        for (int i = n-2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i+1])
                res[i] = res[i+1] + 1;
        }

        // from left to right, if cur rating > prev rating, cur = max(cur, prev + 1)
        for (int i = 1; i< n; i++ ){
            if (ratings[i] > ratings[i-1])
                res[i] = max(res[i], res[i-1]+ 1 );
        }

        return accumulate(res.begin(), res.end(), 0); 
    }
};
// @lc code=end

