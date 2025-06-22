#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1570 lang=cpp
 *
 * [1570] 两个稀疏向量的点积
 */

// @lc code=start
class SparseVector {
    public:
        SparseVector(const vector<int>& nums) {
            for (size_t index = 0; index < nums.size(); ++index) {
                if (nums[index] != 0) {
                    pairs.push_back({index, nums[index]});
                }
            }
        }
    
        int dotProduct(const SparseVector& vec) const {
            int result = 0;
            size_t p = 0, q = 0;
    
            while (p < pairs.size() && q < vec.pairs.size()) {
                if (pairs[p].first == vec.pairs[q].first) {
                    result += pairs[p].second * vec.pairs[q].second;
                    ++p;
                    ++q;
                } else if (pairs[p].first < vec.pairs[q].first) {
                    ++p;
                } else {
                    ++q;
                }
            }
    
            return result;
        }
    
    private:
        vector<pair<int, int>> pairs;
    };

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
// @lc code=end

