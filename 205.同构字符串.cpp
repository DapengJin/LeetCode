#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=205 lang=cpp
 *
 * [205] 同构字符串
 */

// @lc code=start
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> s2t; // !!!「双射」关系
        unordered_map<char, char> t2s;  
        int n = s.size(); 

        for (int i = 0 ;  i< n ; i++) 
        { 
            char x = s[i], y = t[i]; 

            if (s2t.contains(x) && s2t[x] != y || t2s.contains(y) && t2s[y]!= x)
                return false; 

            s2t[x] = y; 
            t2s[y] = x;
        }
        
        return true;         
    }
};
// @lc code=end

