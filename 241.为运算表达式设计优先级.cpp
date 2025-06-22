#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=241 lang=cpp
 *
 * [241] 为运算表达式设计优先级
 */

// @lc code=start
class Solution
{
public:
    // @cache
    vector<int> diffWaysToCompute1(string expression)
    {
        vector<int> res;
        unordered_map<char, function<int(int, int)>> op; // operations

        op['+'] = [](int x, int y) { return x + y; };
        op['-'] = [](int x, int y) { return x - y; };
        op['*'] = [](int x, int y) { return x * y; };

        // while((pos=s.find_first_of("+-*",pos+1))!=s.npos)//找到所有运算符并分左右进行计算
        for (int i = 0; i < expression.size(); i++)
        {
            char c = expression[i];

            if (!op.contains(c))
                continue;

            auto l = diffWaysToCompute1(expression.substr(0, i));
            auto r = diffWaysToCompute1(expression.substr(i + 1));

            for (auto res1 : l)
                for (auto res2 : r)
                    res.push_back(op[c](res1, res2));
        }

        // !!! 'res is empty' means the expression only has a number
        return res.empty() ? vector<int>{stoi(expression)} : res;
    }

    vector<int> diffWaysToCompute(string expression)
    {
        vector<int> nums;
        vector<char> ops;
        int num = 0;
        char op = ' ';
        istringstream ss(expression);
        while (ss >> num)
        {
            nums.push_back(num);
            if (ss >> op)
            {
                ops.push_back(op);
            }
        }
        int n = nums.size();
        /**
         * 
         * dp[i][j] 的含义
         * 
         * dp 是一个 三维动态规划数组，其中 dp[i][j] 是一个 vector<int>，
         * 表示在给定的子表达式范围 [i, j] 内可以通过不同加括号方式计算得到的所有可能的结果集合。
         * 
         * 举例说明
         *
         * 假设表达式为 2-1-1：
         *     •	dp[0][0] = {2} 表示子表达式只包含第一个数字 2 的结果集合。
         *     •	dp[1][2] = {0, -2} 表示子表达式 1-1 的所有可能结果。
         *     •	dp[0][2] = {0, 2} 表示整个表达式 2-1-1 的所有可能结果。
         */
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>()));

        unordered_map<char, function<int(int, int)>> op_funcs;
        op_funcs['+'] = [](int a, int b) { return a + b; };
        op_funcs['-'] = [](int a, int b) { return a - b; };
        op_funcs['*'] = [](int a, int b) { return a * b; };

        /**
         * 正确的填充顺序
         * 
         *  要计算 dp[i][j]，dp[i][k] 和 dp[k+1][j] 必须已经计算好。因此：
         *      •	外层循环 j 控制右边界，确保从小到大逐步扩大范围。
         *      •	内层循环 i 控制左边界，从右到左遍历，确保当前范围 [i, j] 的所有子范围都已被计算。
         * 
         * 
         */
        for (int j = 0; j < n; ++j) // j 表示当前考虑的子表达式的右边界。循环从左到右依次扩大右边界，逐步处理更大的子区间。
            for (int i = j; i >= 0; --i) // i 表示当前子表达式的左边界。通过从右到左的顺序遍历所有可能的左边界，逐步计算从区间 [i, i]（单个数字）到区间 [0, i]（完整子表达式）的所有可能结果。
            {
                if (j == i)
                {
                    dp[i][j].push_back(nums[j]);
                    continue;
                }

                for (int k = i; k < j; ++k)
                    for (auto l : dp[i][k])
                        for (auto r : dp[k + 1][j])
                            dp[i][j].push_back(op_funcs[ops[k]](l, r));
            }

        return dp[0][n - 1];
    }
};
// @lc code=end
