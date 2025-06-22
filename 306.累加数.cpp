#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=306 lang=cpp
 *
 * [306] 累加数
 */

// @lc code=start
class Solution
{
public:
    string add_string(string s1, string s2)
    {
        ranges::reverse(s1);
        ranges::reverse(s2);

        int m = s1.size(), n = s2.size();

        if (m < n)
            swap(s1, s2);

        function<void(int, int)> dfs = [&](int i, int carry)
        {
            if (i >= m)
                if (carry == 0)
                    return;
                else
                {
                    s1 += to_string(carry);
                    return;
                }

            int sum = s1[i] - '0' + (i < n ? s2[i] - '0' : 0) + carry;

            carry = sum / 10;
            s1[i] = sum % 10 + '0';

            dfs(i + 1, carry);
        };

        dfs(0, 0);
        ranges::reverse(s1);

        return s1;
    }

    bool isAdditiveNumber(string num)
    {
        int n = num.size();
        vector<string> path;

        function<bool(int)> dfs = [&](int i) -> bool
        {
            if (i == n)
                if (path.size() < 3)
                    return false;
                else
                    return true;

            for (int j = i; j < n; j++)
            {

                string sub = num.substr(i, j - i + 1);

                if (sub.size() > 1 && sub[0] == '0')
                    return false; // 如果有前导零，跳过这个子串

                int m = path.size();

                if (m < 2 || 
                    add_string(path[m - 1],path[m - 2]) == sub)
                {
                    path.push_back(sub);
                    if (dfs(j + 1))
                        return true;
                    path.pop_back();
                }
            }

            return false;
        };

        return dfs(0);
    }
};
// @lc code=end
