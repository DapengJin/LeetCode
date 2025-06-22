#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2523 lang=cpp
 *
 * [2523] 范围内最接近的两个质数
 */

// @lc code=start
const int MX = 1e6;
vector<int> primes;

/* 埃式筛 */
int init = []() {
    bool np[MX + 1]{};
    for (int i = 2; i <= MX; ++i)
        if (!np[i]) {
            primes.push_back(i);
            // 可以从 i * i 开始，之前的都算过了
            for (int j = i; j <= MX / i; ++j) // 避免溢出的写法
                np[i * j] = true;
        }
    primes.push_back(MX + 1);
    primes.push_back(MX + 1); // 保证下面下标不会越界
    return 0;
}(); // 最后一个 () 表示立即调用 lambda 表达式

/* 线性筛（欧拉筛） */
// int init = []() {
//     bool np[MX + 1]{};
//     for (int i = 2; i <= MX; ++i) {
//         if (!np[i]) primes.push_back(i);
//         for (int p: primes) {
//             if (i * p > MX) break;
//             np[i * p] = true;
//             if (i % p == 0) break;
//         }
//     }
//     primes.push_back(MX + 1);
//     primes.push_back(MX + 1); // 保证下面下标不会越界
//     return 0;
// }();

class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        int p = -1, q = -1;
        int i = lower_bound(primes.begin(), primes.end(), left) - primes.begin();
        for (; primes[i + 1] <= right; ++i)
            if (p < 0 || primes[i + 1] - primes[i] < q - p) {
                p = primes[i];
                q = primes[i + 1];
            }
        return {p, q};
    }
};
// @lc code=end

