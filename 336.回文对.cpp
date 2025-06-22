#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=336 lang=cpp
 *
 * [336] 回文对
 */

// @lc code=start
class Solution {
public:
    bool is_pld(string word)
    { 
        int n = word.size(), l= 0, r = n - 1; 

        while (l < r) 
        { 
            if (word[l] != word[r]) return false;
            
            l++; 
            r--;
        }

        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        int n = words.size();

        for (int i = 0; i < n + 1 ; i++)
            for (int j = i+1; j < n; j++ )
            {
                if (is_pld(words[i] + words[j])) res.push_back({i, j}); 
                if (is_pld(words[j] + words[i])) res.push_back({j, i}); 
            }

        return res; 
    }
};
// @lc code=end

