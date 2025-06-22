#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2212 lang=cpp
 *
 * [2212] 射箭比赛中的最大得分
 */

// @lc code=start
class Solution
{
public:
    vector<int> maximumBobPoints(int numArrows, vector<int> &aliceArrows)
    {
        int res = 0;
        int n = 12;
        vector<int> path(n, 0);
        vector<int> res_path(n, 0);

        /* 选/不选 */
        function<void(int, int, int)> dfs = [&](int i, int left, int score)
        {
            if (i == n) 
            {
                if (score > res)
                {
                    res = score;
                    copy(path.begin(), path.end(), res_path.begin());
                    res_path[0] += left; 
                }

                return;
            }


            dfs(i+1, left, score); 

            if (left > aliceArrows[i])
            { 
                path[i] = aliceArrows[i] + 1;
                dfs(i + 1, left - aliceArrows[i] - 1, score + i);
                path[i] = 0; // 恢复现场
            }

            return;
        };

        dfs(0, numArrows, 0);

        /* 选第几个 */
        // function<void(int, int, int)> dfs = [&](int i, int left, int score)
        // {

        //     if (score > res)
        //     {
        //         res = score;

        //         copy(path.begin(), path.end(), res_path.begin());
        //     }

        //     for (int j = i; j < n; j++)
        //     {
        //         if (left > aliceArrows[j])
        //         {
        //             path[j] = aliceArrows[j] + 1;
        //             dfs(j + 1, left - aliceArrows[j] - 1, score + j);
        //             path[j] = 0; // 恢复现场
        //         }
        //     }

        //     return;
        // };

        // dfs(0, numArrows, 0);

        // // !!! 已经赢了，但是还是要把剩下的箭加在 [0] 上
        // res_path[0] += numArrows - accumulate(res_path.begin(),res_path.end(), 0);

        return res_path;
    }
};
// @lc code=end
