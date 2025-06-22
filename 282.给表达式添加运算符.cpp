#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=282 lang=cpp
 *
 * [282] 给表达式添加运算符
 */

// @lc code=start
class Solution
{
public:
    vector<string> addOperators(string num, int target)
    {
        int n = num.size();
        vector<string> res;

        // "123" -> [1,2,3] [12,3] [1,23]
        // dfs(i)
        //      find dfs(j) where j ∈ [i, n)
        //           dfs(j+1) ... until i == n

        function<void(string, int, long long, long long)>
            dfs = [&](
                      string expr,   // construct the answer
                      int i,         // idx
                      long long sum, // current res
                      long long mul  // the previous number that is added to the res
                  )
        {
            if (i == n)
            {
                if (sum == target)
                    res.push_back(expr);

                return;
            }

            long long val = 0;

            for (int j = i;
                 j < n && (j == i || num[i] != '0'); // no heading 0
                 j++)
            {
                val = val * 10 + num[j] - '0';

                if (i == 0)
                {
                    dfs(to_string(val), j + 1, sum + val, val);
                }
                else
                {
                    dfs(expr + "+" + to_string(val), j + 1, sum + val, val);
                    dfs(expr + "-" + to_string(val), j + 1, sum - val, -val);
                    dfs(expr + "*" + to_string(val), j + 1, sum - mul + mul * val, mul * val);
                }
            }
        };

        dfs("", 0, 0, 0);

        return res;
    }
};
// @lc code=end
