#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1947 lang=cpp
 *
 * [1947] 最大兼容性评分和
 */

// @lc code=start
class Solution
{
public:
    /**
     * 时间复杂度：O(m × 2^m × n)
     *
     * 解释如下：
     *      有 2^m 个状态（s 的取值范围是 [0, 2^m - 1]）。
     *      每个状态最多枚举 m 个学生（最多 m 位为 1）。
     *      对于每对（学生 i, 导师 cnt-1），我们需要花 O(n) 时间计算兼容度（因为答案长度是 n）。
     */
    int maxCompatibilitySum(vector<vector<int>> &students, vector<vector<int>> &mentors)
    {
        int m = students.size();    // 学生 / 导师的数量
        int n = students[0].size(); // 每人回答的问题数

        // 状态压缩 DP 解法
        // dp[s] 表示：当前状态 s（二进制中哪些导师已被分配），
        // 将前 cnt = __builtin_popcount(s) 个学生 与这些导师一一匹配后的最大兼容度总和

        vector<int> dp(1 << m, 0); // 共有 2^m 个状态（导师的分配组合）

        // 枚举所有导师的分配状态（即 2^m 个状态）
        for (int s = 1; s < (1 << m); s++)
        {
            int cnt = __builtin_popcount(s); // 当前匹配了 cnt 位学生，即将匹配第 cnt-1 个学生

            // 枚举当前状态下所有被选中的导师（即 s 中为 1 的位）
            for (int i = 0; i < m; i++)
            {
                if ((s >> i) & 1) // 如果第 i 位为 1，表示导师 i 已被使用，可以和当前学生配对
                {
                    // 计算学生 cnt-1 与导师 i 的兼容度
                    int g = 0;
                    for (int j = 0; j < n; j++)
                    {
                        if (students[cnt - 1][j] == mentors[i][j])
                        {
                            g++;
                        }
                    }

                    // 状态转移：
                    // 从状态 s ^ (1 << i)（即没有用导师 i 的状态）转移到当前状态 s，
                    // 把第 cnt-1 个学生分配给导师 i
                    dp[s] = max(dp[s], dp[s ^ (1 << i)] + g);
                }
            }
        }

        return dp.back(); // 返回全 1 状态（所有导师都被分配）下的最大兼容度总和
    }
};
// @lc code=end
