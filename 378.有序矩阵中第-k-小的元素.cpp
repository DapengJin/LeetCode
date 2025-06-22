#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=378 lang=cpp
 *
 * [378] 有序矩阵中第 K 小的元素
 */

// @lc code=start
class Solution
{
public:
    // O(n · log(range))
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        int m = matrix.size(), n = matrix[0].size(); 

        // check(mid)：判断矩阵中是否至少有 k 个元素 ≤ mid
        auto check = [&](int mid) -> bool // 如是 return true
        { 
            int i = 0, j = n-1, cnt =0 ; 

            // “右上”→“左下”遍历，每步排除一行或一列
            // mid == 8 见图 [./378.mid=8.png]
            while (i < m && j >=0)
                // 当前元素比 mid 大，说明本列这一行及其下方所有元素也都大
                if (matrix[i][j] > mid) j--; // 所以向左移一列
                else // matrix[i][j] ≤ mid
                { 
                    cnt += j + 1; // 本行 [0..j] 列的元素都 ≤ mid
                    i++;          // 移动到下一行继续统计
                }

            // 如果统计数 ≥ k，说明第 k 小的元素 ≤ mid
            return cnt >= k; 
        };

        // 在值域上二分
        int l = matrix[0][0] - 1;
        int r = matrix[m-1][n-1] + 1; 

        while (l+ 1 < r) 
        { 
            int mid = (l + r ) / 2; 

            if (check(mid))
                // 至少有 k 个 ≤ mid，说明第 k 小 ≤ mid
                r = mid; 
            else 
                l = mid;
        }

        return r; 
    }
};
// @lc code=end
class Solution
{
public:
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        int n = matrix.size();
        // 使用 tuple<int val, int x, int y> 和 greater 比较器构建小顶堆
        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>>
            pq;

        // 1. 将每一行的第一个元素 (val, row, col) 入堆
        for (int i = 0; i < n; ++i)
            pq.emplace(matrix[i][0], i, 0);

        // 2. 弹出 k-1 次；每次弹出后，将同一行的下一个元素入堆
        for (int cnt = 0; cnt < k - 1; ++cnt)
        {
            auto [val, x, y] = pq.top(); pq.pop();

            if (y + 1 < n)
                pq.emplace(matrix[x][y + 1], x, y + 1);
        }

        // 3. 堆顶即为第 k 小的元素
        return get<0>(pq.top());
    }
};