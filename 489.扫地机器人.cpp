#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=489 lang=cpp
 *
 * [489] 扫地机器人
 *
房间中的某个位置上有一个机器人，你需要控制它清扫房间。房间被建模为一个 m x n 的二进制网格，其中 0 表示单元格中有障碍物，1 表示空单元格。

机器人从一个未知的空单元格开始出发，并且你无法访问网格，但你可以使用给定的 API Robot 控制机器人。

你的任务是使用机器人清扫整个房间（即清理房间中的每个空单元格）。机器人具有四个给定的API，可以前进、向左转或向右转。每次转弯 90 度。

当机器人试图移动到一个存在障碍物的单元格时，它的碰撞传感器会检测到障碍物，并停留在当前单元格。

设计一个算法，使用下述 API 清扫整个房间：

interface Robot {
  // 若下一个单元格为空，则返回 true ，并移动至该单元格。
  // 若下一个单元格为障碍物，则返回 false ，并停留在当前单元格。
  boolean move();

  // 在调用 turnLeft/turnRight 后机器人会停留在当前单元格。
  // 每次转弯 90 度。
  void turnLeft();
  void turnRight();

  // 清理当前单元格。
  void clean();
}
注意 扫地机器人的初始方向向上。你可以假定网格的四周都被墙包围。



自定义测试：

输入只用于初始化房间和机器人的位置。你需要「盲解」这个问题。换而言之，你必须在对房间和机器人位置一无所知的情况下，只使用 4 个给出的 API 解决问题。



示例 1：


输入：room = [[1,1,1,1,1,0,1,1],[1,1,1,1,1,0,1,1],[1,0,1,1,1,1,1,1],[0,0,0,1,0,0,0,0],[1,1,1,1,1,1,1,1]], row = 1, col = 3
输出：Robot cleaned all rooms.
解释：
房间内的所有单元格用 0 或 1 填充。
0 表示障碍物，1 表示可以通过。
机器人从 row=1, col=3 的初始位置出发。
在左上角的一行以下，三列以右。
示例 2：

输入：room = [[1]], row = 0, col = 0
输出：Robot cleaned all rooms.


提示：

m == room.length
n == room[i].length
1 <= m <= 100
1 <= n <= 200
room[i][j] 为 0 或 1.
0 <= row < m
0 <= col < n
room[row][col] == 1
所有空单元格都可以从起始位置出发访问到。
 */


// This is the robot's control interface.
// You should not implement it, or speculate about its implementation
class Robot {
  public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move();

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft();
    void turnRight();

    // Clean the current cell.
    void clean();
};

// @lc code=start
class Solution
{
public:
    void cleanRoom(Robot &robot)
    {
        // 方向数组：0=上, 1=右, 2=下, 3=左，对应的坐标增量 (dx, dy)
        vector<pair<int, int>> dirs = {
            {-1, 0}, // 上
            {0, 1},  // 右
            {1, 0},  // 下
            {0, -1}  // 左
        };

        // 辅助函数：将坐标 (x,y) 转成唯一字符串
        auto key = [&](int x, int y)
        {
            return to_string(x) + "," + to_string(y);
        };

        // 回退函数：将机器人从当前位置返回到上一个位置，并恢复朝向
        auto move_back = [&]()
        {
            robot.turnRight();
            robot.turnRight();
            robot.move();
            robot.turnRight();
            robot.turnRight();
        };

        // 记录已访问格子，用字符串 "x,y" 作为 key
        unordered_set<string> visited;

        // 递归回溯函数：从 (x,y) 出发，当前面向方向 d
        function<void(int, int, int)> dfs = [&](int x, int y, int d)
        {
            // 标记并清扫当前格子
            visited.insert(key(x, y));
            robot.clean();

            // 按顺时针方向依次尝试 4 个方向
            for (int i = 0; i < 4; ++i)
            {
                int nd = (d + i) % 4;         // 新方向索引
                int nx = x + dirs[nd].first;  // 新的 x 坐标
                int ny = y + dirs[nd].second; // 新的 y 坐标
                string nk = key(nx, ny);

                // 如果新格子未访问且机器人能移动过去
                if (!visited.contains(nk) && robot.move())
                {
                    // 递归进入该格子
                    dfs(nx, ny, nd);
                    // 回退到 (x,y) 并恢复朝向
                    move_back();
                }

                // 旋转机器人，使其面向下一个方向
                robot.turnRight();
            }
        };

        // 从 (0,0) 开始，初始朝向“上”（方向索引 0）
        dfs(0, 0, 0);
    }
};
// @lc code=end
