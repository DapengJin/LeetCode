#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=496 lang=cpp
 *
 * [496] 下一个更大元素 I
 */

// @lc code=start
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        unordered_map<int, int> dict;  // {val : idx} in nums1
        vector<int> res(n, -1); 

        for (int i =0 ; i < n ; i++) 
            dict[nums1[i]] = i; 

        stack<int> s; // idx in nums2

        // // 从左到右
        // for(int i = 0 ; i< m ; i++)
        // { 
        //     while (!s.empty() && nums2[i] > nums2[s.top()])
        //     {
        //         int idx2 = s.top(), val = nums2[idx2]; 
        //         s.pop(); 

        //         if (dict.contains(val))
        //             res[dict[val]] = nums2[i]; 
        //     }

        //     s.push(i); 
        // }

        // 从右到左
        for (int i = m-1; i >=0; i--)
        {
            while (!s.empty() && nums2[i] > nums2[s.top()])
                s.pop();

            if (!s.empty() && dict.contains(nums2[i]))
                res[dict[nums2[i]]] = nums2[s.top()]; 
            
            s.push(i); 
        }

        return res; 
    }
};
// @lc code=end

