#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=91 lang=cpp
 *
 * [91] 解码方法
 */

// @lc code=start
class Solution {
    public:
        int numDecodings(string s) {
            // e.g. if s == "226", s will be "00226"
            // start with s[2]
            s = "00" + s; 
    
            // dp == 01000... start with dp[2]
            vector<int> dp(s.size(), 0);
            dp[1] = 1;
    
            int n = dp.size();
    
            for (int i = 2; i < n; i++) { 
                if (s[i] != '0') 
                    dp[i] = dp[i] + dp[i-1]; 
                if (s[i-1] == '1' || 
                    (s[i-1] == '2' && s[i] <= '6'))
                    dp[i] = dp[i] + dp[i-2]; 
            }
    
            return dp[n-1]; 
        }
    };
// @lc code=end

