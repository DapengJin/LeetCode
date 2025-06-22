#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1439 lang=cpp
 *
 * [1439] 有序矩阵中的第 k 个最小数组和
 */

// @lc code=start

/* 暴力 */
/** O(mnk * log(nk))
class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        # 初始化：从第一行取前 k 个元素，作为“候选和数组”
        a = mat[0][:k]

        # 从第二行开始，依次和“当前的候选数组 a”进行组合
        for row in mat[1:]:
            # 枚举所有 x + y 后排序并只保留前 k 小的和
            a = sorted(x + y for x in a for y in row)[:k]

        # 最终我们已经找到了前 k 小的和，返回第 k 小的值（排好序了）
        return a[-1]
 */
class Solution
{
public:
    int kthSmallest(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();

        // 预先计算所有最小值之和 sl，和所有最大值之和 sr
        int sl = 0, sr = 0;
        for (auto &row : mat)
        {
            sl += row[0];
            sr += row.back();
        }

        // dfs 判断当前是否可以构造出 >= k 个子数组和 ≤ mid
        function<bool(int, int &, int)> dfs = [&](int i, int &left_k, int budget) -> bool
        {
            if (i == m)
                return --left_k == 0;

            for (int x : mat[i])
            {
                int extra = x - mat[i][0]; // 当前元素比最小值多加的值

                if (extra > budget)
                    break; // 剪枝：超出预算就停止
                    
                if (dfs(i + 1, left_k, budget - extra))
                    return true;
            }

            return false;
        };

        // 二分：找最小的数组和，使得 ≤ 它的子数组和数量 ≥ k
        int l = sl - 1; // l 左侧的 s 都满足 f(s) <  k
        int r = sr + 1; // r 右侧的 s 都满足 f(s) >= k

        while (l + 1 < r)
        {
            int mid = (l + r) / 2;
            int left_k = k;

            if (dfs(0, left_k, mid - sl)) // 预算为 mid - sl（默认选了每行最小值）
                r = mid;
            else
                l = mid;
        }

        return r;
    }
};
// @lc code=end
