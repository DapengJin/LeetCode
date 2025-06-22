
#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=253 lang=cpp
 *
 * [253] 会议室 II
 * 
 * 
 * 
 * 给你一个会议时间安排的数组 intervals ，每个会议时间都会包括开始和结束的时间 intervals[i] = [starti, endi] ，
 * 返回 所需会议室的最小数量 。
 * 
 * 示例 1：
 *     输入：intervals = [[0,30],[5,10],[15,20]]
 *     输出：2
 * 
 * 示例 2：
 *     输入：intervals = [[7,10],[2,4]]
 *     输出：1
 *  
 * 提示：
 *     1 <= intervals.length <= 104
 *     0 <= starti < endi <= 106
 * 
 */

// @lc code=start
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int res = 0, n = intervals.size(); 

        priority_queue<int, vector<int>, greater<int>> q; // 最小堆

        sort(intervals.begin(), intervals.end()); // 根据开始时间排序会议
        q.emplace(intervals[0][1]); // 添加 第一个会议 的结束时间

        for (int i = 1 ; i < n ; i ++)
        { 
            int s = intervals[i][0], e = intervals[i][1]; 

            if (s >= q.top()) // 会议结束
            {
                q.pop(); // 腾出老房间
            }

            // 使用老房间 或 分配新房间
            q.push(e); 
        }

        return q.size(); 
    }
};
// @lc code=end

