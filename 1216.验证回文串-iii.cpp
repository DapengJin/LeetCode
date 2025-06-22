#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1216 lang=cpp
 *
 * [1216] 验证回文串 III
 */

// @lc code=start
class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size(); 

        vector f(n, vector(n, 0)); 

        for (int i = n - 2; i >= 0; i--)
            for (int j = i + 1; j < n ; j++)
            { 
                if (s[i] != s[j])
                    f[i][j] = 1 + min(f[i+1][j], f[i][j-1]); 
                
                else 
                    f[i][j] = f[i+1][j-1];
            }
    
        return f[0][n-1] <= k; 
    }
};
// @lc code=end

