#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=88 lang=cpp
 *
 * [88] 合并两个有序数组
 */

// @lc code=start
class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int i = m + n - 1; // update the last elem
        int p1 = m - 1, p2 = n - 1;

        while (p1 >= 0 && p2 >= 0)
        {
            if (nums1[p1] > nums2[p2])
            {
                nums1[i] = nums1[p1];
                p1--;
            }
            else
            {
                nums1[i] = nums2[p2];
                p2--;
            }

            i--;
        }

        // 如果 p2 还剩下了，继续把 p2 复制到 p1
        while (i >= 0 && p2 >= 0)
        {
            nums1[i] = nums2[p2];
            i--;
            p2--;
        }
    }
};
// @lc code=end

/** follow up 合并 3 个有序数组 + 去重 */
class Solution1
{
public:
    vector<int> mergeThreeSortedArrays(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        vector<int> res;
        int i = 0, j = 0, k = 0;

        while (i < A.size() || j < B.size() || k < C.size())
        {
            int val = INT_MAX;

            if (i < A.size()) val = min(val, A[i]);
            if (j < B.size()) val = min(val, B[j]);
            if (k < C.size()) val = min(val, C[k]);

            if (res.empty() || res.back()!= val)
                res.push_back(val);

            if (i < A.size() && A[i] == val) i++;
            if (j < B.size() && B[j] == val) j++;
            if (k < C.size() && C[k] == val) k++;
        }

        return res;
    }
};

int main() {
    vector<int> A = {-1, -1, 0, 1};
    vector<int> B = {-2, 3, 5};
    vector<int> C = {-1, 0, 5};
    Solution1 s;
    vector<int> result = s.mergeThreeSortedArrays(A, B, C);
    
    cout << "合并后的有序数组：";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}