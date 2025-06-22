#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1239 lang=cpp
 *
 * [1239] 串联字符串的最大长度
 */

// @lc code=start
class Solution
{
public:
    int maxLength(vector<string> &arr)
    {
        int n = arr.size();
        int res = 0;

        /* 选/不选 */
        // function<void(int, string)> dfs = [&](int i, string s) -> void
        // {
        //     if (i == n)
        //     {
        //         res = max(res, (int)s.size());
        //         return;
        //     }

        //     dfs(i + 1, s); // 不选

        //     string new_s = s + arr[i];
        //     unordered_set<char> count;

        //     for (auto c : new_s)
        //         if (count.contains(c))
        //             return; // 提前返回
        //         else
        //             count.insert(c);

        //     dfs(i + 1, new_s); // 都是单独的字母就选，要不就 提前返回
        // };

        /* 选哪个 */
        function<void(int, string)> dfs = [&](int i, string s) -> void
        {
            res = max(res, (int)s.size());

            if (i == n)
                return;

            for (int j = i; j < n; j++)
            {
                string new_s = s + arr[j];
                unordered_set<char> count;
                bool is_uni = true;

                for (auto c : new_s)
                    if (count.contains(c))
                    {
                        is_uni = false;
                        // !!! 不能直接 continue
                        break; // 不是unique，寻找下一个
                    }
                    else
                        count.insert(c);

                if (is_uni)
                    dfs(j + 1, new_s);
            }
        };

        dfs(0, "");

        return res;
    }
};
// @lc code=end
