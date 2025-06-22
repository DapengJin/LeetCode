#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=650 lang=cpp
 *
 * [650] 两个键的键盘
 */

// @lc code=start

// 贪心：将 n 分解为质因数之和即为最小操作数
/**
 * 证明要点：
 * - 将一次 "Copy All + (k-1)×Paste" 操作视为一次“动作”，其效果是把当前的字符数从 x 变为 x×k，总共消耗 k 步。
 * - 假设我们依次执行了若干次这样的乘法动作，每次扩大为当前字符数的 k 倍：
 *     从 1 个 'A' 开始：
 *     第一步乘以 k1 → 得到 k1 个 'A'（耗费 k1 步）
 *     第二步乘以 k2 → 得到 k1×k2 个 'A'（耗费 k2 步）
 *     ...
 *     最后一步乘以 kr → 得到 k1×k2×...×kr = n 个 'A'（耗费 kr 步）
 * 
 * - 总操作次数 = k1 + k2 + ... + kr。
 * 
 * - 要让乘积为 n 的同时使因子和最小，最佳策略是只使用质因子。
 *   因为对于任意合数 m = a*b (a,b ≥ 2)，有 a*b ≥ a + b，拆分会带来不更高的总耗费。
 * - 因此，对 n 进行质因数分解，累加所有质因子，就是最少操作数。
 *
 */
class Solution
{
public:
    int minSteps(int n)
    {
        int res = 0;

        // 从 2 开始尝试所有可能的因子
        for (int i = 2; i * i <= n; i++)
        {
            // 当 i 是 n 的因子时，不断“剪切”并添加操作数
            while (n % i == 0)
            {
                res += i; // 对于因子 i，需要一次 Copy All 和 i-1 次 Paste，共计 i 步
                n /= i;   // 将问题规模缩小到 n/i
            }
        }

        // 如果循环结束后 n>1（剩余一个大于 sqrt 原 n 的质因数），也要计入
        if (n > 1)
            res += n;

        return res;
    }
};
// @lc code=end

/* DP */
// 动态规划：状态 f[i] 表示得到 i 个 'A' 的最少操作数
class Solution1
{
public:
    int minSteps(int n)
    {
        // 初始化：所有状态设为大数，除 f[1]=0
        vector<int> f(n + 1, INT_MAX / 2);
        f[1] = 0;

        // 计算每个 f[i]
        for (int i = 2; i <= n; i++)
        {
            // 只需枚举到 sqrt(i) 寻找因子
            for (int j = 1; j * j <= i; j++)
            {
                if (i % j == 0)
                {
                    int d = i / j;
                    // 如果 j 是因子，则可由 f[j] "复制粘贴"得到 i：
                    // 先用 f[j] 步得到 j 个 'A'，再 Copy All + (i/j - 1) 次 Paste，共计 f[j] + d 步
                    f[i] = min(f[i], f[j] + d);
                    // 对应的因子对 d -> j：由 f[d] 得到 d 个 'A'，再 Paste j-1 次 => f[d] + j
                    f[i] = min(f[i], f[d] + j);
                }
            }
        }

        return f[n];
    }
};