#include "pkgs.h"
/*
 * @lc app=leetcode id=76 lang=cpp
 *
 * [76] Minimum Window Substring
 */

// @lc code=start
class Solution
{
public:
    string minWindow(string s, string t)
    {
        vector<bool> valid(128, false);
        vector<int> freq(128, 0);

        // count the freq and valid
        for (auto c : t)
        {
            valid[c] = true;
            freq[c]++;
        }

        // if count == t.length(), we find all the chars in t
        int count = 0, min_l = -1, min_len = INT_MAX;

        for (int l = 0, r = 0; r < s.length(); r++)
        {
            if (!valid[s[r]])
                continue;

            if (--freq[s[r]] >= 0)
            {
                count++;
            }

            if (count == t.length())
            {
                while (true)
                {
                    if (!valid[s[l]])
                    {
                        l++;
                        continue;
                    }

                    // find the min window, don't change the l and freq
                    if (freq[s[l]] + 1 > 0)
                    {
                        // update min_len
                        if (min_len > r - l + 1)
                        {
                            min_l = l;
                            min_len = r - l + 1;
                        }

                        // break
                        break;
                    }
                    else
                    {
                        // !!! the order is wrong
                        // l++;
                        // freq[s[l]]++;

                        freq[s[l]]++;
                        l++;
                    }
                }
            }
        }

        return min_l == -1 ? "" : s.substr(min_l, min_len);
    }
};
// @lc code=end

int main()
{
    Solution solution;
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";
    std::string result = solution.minWindow(s, t);
    std::cout << "The minimum window substring is: " << result << std::endl;
    return 0;
}