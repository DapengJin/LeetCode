#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=373 lang=cpp
 *
 * [373] 查找和最小的 K 对数字
 */

// @lc code=start
class Solution {
public:
    /**
     * 和 k 路 合并 的区别是：最小值必须 from 不同数组
     * 
     *   - 若只添加 (sum, 0, 0) 
     *              -> (1, 0) + (0, 1) 
     *              -> (1, 1) + (1, 1) 
     *     如何去重？
     *      - ❌ 用 set 去重 （可以，不是最优）
     *      - ✅ 添加 (sum, i, 0) 出堆的时候 只用考虑 (i, j+1) 而不是 (i+1, j) 和 (i, j+1)
     */
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size(); 
        priority_queue<tuple<int,int,int>> pq; // (nums1[i] + nums2[j], i, j)

        for (int i = 0 ; i < min(k, m); i++)
            pq.push({-(nums1[i] + nums2[0]), i, 0});

            vector<vector<int>> ans; 

        while (ans.size() < k) 
        { 
            auto [_, i , j] = pq.top(); pq.pop(); 

            ans.push_back({nums1[i], nums2[j]}); 

            int nxt_j = j+1;

            if (nxt_j < n) pq.push({-(nums1[i] + nums2[nxt_j]), i, nxt_j});
        }

        return ans; 
    }
};
// @lc code=end

