#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2532 lang=cpp
 *
 * [2532] 过桥的时间
 */

// @lc code=start

/**
 *
 * 1. 把完成 pick / put 的工人 都放在桥边排队
 *    这个是 batch processing
 * 2. right 先过桥 (必须所有人都过完桥之后 left 才能过)
 *    left  后过桥，如果人已经足够搬 右边的所有箱子了 就 不用过桥了
 *    这个是 一个一个 process 的 (if right, else left)
 * 3. 如果没人在桥边等 == 都在搬箱子，跳到第一个搬完箱子的时间
 *
 *
 *
 *  left / new                          right / old
 *       🏠 <——————————————桥———————————————— 📦
 *
 *                    (0) right
 *       👷 (3) put   ——————————>  (1) pick
 *                   <——————————
 *                     (2) left
 *
 */
class Solution
{
public:
    int findCrossingTime(int n, int k, vector<vector<int>> &time)
    {
        stable_sort(time.begin(), time.end(), [](auto &a, auto &b)
                    { return a[0] + a[2] < b[0] + b[2]; });

        // (idx, time) 在等待队列里 time 不重要了，需要效率低的人先过
        priority_queue<pair<int, int>> waitL, waitR;
        // (time, idx)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> workL, workR;
        for (int i = k - 1; i >= 0; --i)
            waitL.emplace(i, 0); // 下标越大效率越低

        int cur = 0;
        while (n)
        {
            // 1. 把完成 pick / put 的工人 都放在桥边排队
            while (!workL.empty() && workL.top().first <= cur)
            {
                auto [t, i] = workL.top();
                workL.pop();
                waitL.emplace(i, t); // 左边完成放箱
            }
            while (!workR.empty() && workR.top().first <= cur)
            {
                auto [t, i] = workR.top();
                workR.pop();
                waitR.emplace(i, t); // 右边完成搬箱
            }

            // 2. 右边先过一个人，注意加到 waitR 中的都是 <= cur 的（下同）
            if (!waitR.empty()) //
            {
                auto [i, t] = waitR.top();
                waitR.pop();
                cur += time[i][2];
                workL.emplace(cur + time[i][3], i); // 放箱
            }
            // 左边过一个人
            else if (!waitL.empty())
            {
                auto [i, t] = waitL.top();
                waitL.pop();
                cur += time[i][0];
                workR.emplace(cur + time[i][1], i); // 搬箱
                --n;
            }

            // 3. cur time 大家都在搬箱子，时间强行跳到 第一个搬完箱子的时间
            else if (workL.empty())
                cur = workR.top().first; // cur 过小，找个最小的放箱/搬箱完成时间来更新 cur
            else if (workR.empty())
                cur = workL.top().first;
            else
                cur = min(workL.top().first, workR.top().first);
        }

        // 右边搬箱 && 过桥
        while (!workR.empty())
        {
            auto [t, i] = workR.top(); // 右边完成搬箱
            workR.pop();
            // 如果没有排队，直接过桥；否则由于无论谁先过桥，最终完成时间都一样，所以也可以直接计算
            cur = max(t, cur) + time[i][2];
        }

        return cur; // 最后一个过桥的时间
    }
};
// @lc code=end
