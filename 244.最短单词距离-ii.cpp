#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=244 lang=cpp
 *
 * [244] 最短单词距离 II
 */

// @lc code=start
class WordDistance {
private: 
    unordered_map<string, vector<int>> indices; // {string : [indices] }
public:

    WordDistance(vector<string>& wordsDict) {
        int n = wordsDict.size(); 

        for (int i = 0 ; i < n ; i++ ){ 
            indices[wordsDict[i]].push_back(i); 
        }
    }
    
    int shortest(string word1, string word2) {
        auto i1 = indices[word1]; 
        auto i2 = indices[word2]; 

        int i = 0, j = 0, res = INT_MAX, m = i1.size(), n = i2.size(); 

        while (i < m && j < n){
            res = min(res, abs(i1[i] - i2[j])); 

            /**
             *  1 3 5 6
             *        i
             *  4 7
             *    j
             */
            if (i1[i] > i2[j]){
                j++; 
            }
            else 
                i++; 
        }   

        return res; 
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */
// @lc code=end

