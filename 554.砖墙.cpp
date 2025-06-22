#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=554 lang=cpp
 *
 * [554] 砖墙
 */

// @lc code=start
class Solution
{
public:
    int leastBricks(vector<vector<int>> &wall)
    {
        int n = wall.size();
        unordered_map<int, int> map; // 存储“每个缝隙的位置”出现的次数（缝隙用前缀和位置表示）

        for (int i = 0, sum = 0; i < n; i++, sum = 0)
        {
            // 遍历当前行的砖块
            for (int cur : wall[i])
            {
                sum += cur; // 当前砖块的右边缘位置（前缀和
                map[sum]++; // 在该位置增加一个缝隙的计数
            }

            map.erase(sum); // 不能从两边穿过，需要 remove 掉最后一个
        }

        int ans = n;

        // 遍历所有缝隙位置，找出最多的缝隙
        for (auto &[u, cnt] : map)
        {
            ans = min(ans, n - cnt); // 穿过缝隙位置 cnt 次，意味着穿过砖块 n - cnt 次
        }

        return ans;
    }
};
// @lc code=end
