#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2040 lang=cpp
 *
 * [2040] 两个有序数组的第 K 小乘积
 */

// @lc code=start
class Solution
{
public:
    long long kthSmallestProduct(vector<int> &nums1, vector<int> &nums2, long long k)
    {
        vector<int> A1, A2, B1, B2;

        // nums: [-3,-2,-1,1,2,3] -> A1:[1,2,3] A2:[1,2,3]
        seperate(nums1, A1, A2); 
        seperate(nums2, B1, B2);

        int neg = A1.size() * B2.size() + A2.size() * B1.size();
        int sign = 1;

        if (k > neg)
            k -= neg;
        else
        {
            k = neg - k + 1; // -5 -4 -3 -2 -1  k = 1 (第一小) return -5
            sign = -1;       // [1, 2, 3, 4, 5] k = 5（第五小） return 5
            swap(B1, B2);
        }

        //                        l          mid       r
        // product < k-th product (p1 p2 p3       p4 p5) product >= k-th product
        // 要找 max(product) = k-th product
        long l = -1;       // products <  k-th product
        long r = 1e10 + 1; // products >= k-th product

        while (l + 1 < r)
        {
            // product 是 m 
            long m = (l + r) / 2;

            if (prod_no_greater_than(m, A1, B1) +
                prod_no_greater_than(m, A2, B2) >= k)
                r = m;
            else
                l = m;
        }

        return sign * r;
    }

private:
    void seperate(const vector<int> &A, vector<int> &A1, vector<int> &A2)
    {
        for (const int a : A)
            if (a < 0)
                A1.push_back(-a);
            else
                A2.push_back(a);
        reverse(A1.begin(), A1.end()); // Reverse to sort ascending
    }

    long prod_no_greater_than(long m, const vector<int> &A, const vector<int> &B)
    {
        long count = 0;
        int j = B.size() - 1;
        // For each a, find the first index j s.t. a * B[j] <= m
        // So numProductNoGreaterThan m for this row will be j + 1
        for (const long a : A)
        {
            while (j >= 0 && a * B[j] > m)
                --j;
            count += j + 1;
        }
        return count;
    }
};
// @lc code=end
