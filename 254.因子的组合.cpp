#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=254 lang=cpp
 *
 * [254] 因子的组合
 * 
 * 整数可以被看作是其因子的乘积。

例如：

8 = 2 x 2 x 2;
  = 2 x 4.
请实现一个函数，该函数接收一个整数 n 并返回该整数所有的因子组合。

注意：

你可以假定 n 为永远为正数。
因子必须大于 1 并且小于 n。

示例 1：
    输入: 1
    输出: []

示例 2：
    输入: 37
    输出: []

示例 3：
    输入: 12
    输出:
    [
    [2, 6],
    [2, 2, 3],
    [3, 4]
    ]

示例 4:
    输入: 32
    输出:
    [
    [2, 16],
    [2, 2, 8],
    [2, 2, 2, 4],
    [2, 2, 2, 2, 2],
    [2, 4, 4],
    [4, 8]
    ]
 

提示：

1 <= n <= 107
 */

// @lc code=start
class Solution
{
public:
    // dfs(i) = dfs(j)
    /*
        dfs(2, 12)        path = []
          dfs(2, 6)       path = [2]
            dfs(2, 3)     path = [2, 2]
              dfs(3, 1)   path = [2, 2, 3]   ✅ push
            dfs(6, 1)     path = [2, 6]      ✅ push
          dfs(3, 4)       path = [3]
            dfs(4, 1)     path = [3, 4]      ✅ push
    */
    vector<vector<int>> getFactors(int n)
    {
        vector<vector<int>> res;
        vector<int> path;

        function<void(int, int)> dfs = [&](int i, int left)
        {
            if (left == 1)
            {
                // 防止 n = 1 的情况
                if (path.size() > 1)
                    res.push_back(path);
                return;
            }

            // n / 2 可以优化一半，而且排除 返回 n 本身的可能
            for (int j = i; j <= min(left, n / 2); j++)
            {
                if (left % j != 0)
                    continue;
                path.push_back(j);
                dfs(j, left / j);
                path.pop_back();
            }
        };

        dfs(2, n);

        return res;
    }
};
// @lc code=end

class Solution
{
public:
    vector<vector<int>> getFactors(int n)
    {
        vector<vector<int>> factorsList;
        vector<int> temp;
        getFactors(n, 2, factorsList, temp);
        return factorsList;
    }

    void getFactors(int num, int start, vector<vector<int>> &factorsList, vector<int> &temp)
    {
        int size = temp.size();
        if (num == 1)
        {
            if (size > 1)
            {
                factorsList.push_back(temp);
            }
        }
        else
        {
            // 分解 num，你只需要尝试到它的平方根就够了。
            // x * x = num  x ⬆️ * x ⬇️ 已经被之前大的计算过了
            // 假设 num = 12  它的因数对有：1×12  2×6  3×4
            int sqrtNum = static_cast<int>(sqrt(num));
            for (int i = start; i <= sqrtNum; i++)
            {
                if (num % i == 0)
                {
                    temp.push_back(i);
                    getFactors(num / i, i, factorsList, temp);
                    temp.pop_back();
                }
            }

            // 最后一个递归：为什么还要再调用一次？
            // 为了处理像 [3, 4] 这样的组合（最后一个因子本身也是有效的乘法因子）。
            temp.push_back(num);
            getFactors(1, num, factorsList, temp);
            temp.pop_back();
        }
    }
};