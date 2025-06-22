#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1279 lang=cpp
 *
 * [1279] 红绿灯路口
 */

// @lc code=start
class TrafficLight
{
    int currentGreenRoad = 1;
    mutex mtx;

public:
    void carArrived(
        int carId,                  // ID of the car
        int roadId,                 // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,              // Direction of the car
        function<void()> turnGreen, // Use turnGreen() to turn light to green on current road
        function<void()> crossCar   // Use crossCar() to make car cross the intersection
    )
    {
        unique_lock<mutex> lock(mtx);

        // 如果当前绿灯不是车辆所在的道路，先切换信号灯
        if (currentGreenRoad != roadId)
        {
            turnGreen();               // 切换绿灯
            currentGreenRoad = roadId; // 更新当前绿灯的道路
        }

        // 车辆通过路口
        crossCar();

        return;
    }
};
// @lc code=end
class TrafficLight1
{
private:
    shared_mutex rwLock;      // 读写锁
    int currentGreenRoad = 1; // 初始绿灯方向：road A (1)

public:
    void carArrived(
        int carId,                  // 车辆 ID
        int roadId,                 // 道路 ID（1 = A, 2 = B）
        int direction,              // 行驶方向
        function<void()> turnGreen, // 切换信号灯回调
        function<void()> crossCar   // 让车辆通过的回调
    )
    {
        { // 读锁作用域
            shared_lock<shared_mutex> readLock(rwLock);
            if (currentGreenRoad == roadId)
            {
                // 当前绿灯方向匹配，直接通过
                crossCar();
                return;
            }
        }

        // 需要更改信号灯，获取写锁
        unique_lock<shared_mutex> writeLock(rwLock);
        if (currentGreenRoad != roadId)
        { // 再次检查，防止其他线程已经修改了
            turnGreen();
            currentGreenRoad = roadId;
        }

        // 让车辆通过
        crossCar();
    }
};