#include "pkgs.h"
/**
 * 大概就是给很多砖，一个list.
 * 每种砖有三个变量, 数量, 这种砖的最大承重（包括自重), 砖的自重，每个砖的高度都是1.
 * 问，如果要堆出一个尽可能高的只有1块砖宽（一块叠另一块上面)的砖墙，这个最大高度是多少.
 */
 class Solution {
 public:
     int maxHeight(vector<tuple<int, int, int>>& bricks)
     {
        vector<int> f;

        f.push_back(0); // f[0] = 0 摆第 0 块砖的时候 total weight = 0

     }
 };