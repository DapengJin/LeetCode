#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1117 lang=cpp
 *
 * [1117] H2O 生成
 */

// @lc code=start
class H2O
{
    condition_variable cv;
    mutex mtx;
    int cnt_h = 0;

public:
    H2O()
    {
    }

    void hydrogen(function<void()> releaseHydrogen)
    {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this]
                { return cnt_h < 2; });

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        cnt_h++;

        if (cnt_h == 2)
            cv.notify_one(); // 没有释放锁就去notify会出问题的吧
                             // 不会，notify时，等待唤醒的线程会被移到锁的竞争队列中，但必须等待释放锁后才能真正执行
    }

    void oxygen(function<void()> releaseOxygen)
    {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this]
                { return cnt_h == 2; });

        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        cnt_h = 0;

        cv.notify_all();
    }
};
// @lc code=end

/* https://leetcode.cn/problems/building-h2o/solutions/1/c-shou-xie-xin-hao-liang-man-zu-ti-mu-yao-qiu-de-x */
class Semaphore
{
private:
    int n_;
    mutex mu_;
    condition_variable cv_;

public:
    Semaphore(int n) : n_{n} {}

public:
    void wait()
    {
        unique_lock<mutex> lock(mu_);
        if (n_ == 0)
        {
            cv_.wait(lock, [this]
                     { return n_ != 0; });
        }
        --n_;
    }

    void signal()
    {
        unique_lock<mutex> lock(mu_);
        ++n_;
        cv_.notify_one();
    }
};

class H2O1
{
private:
    Semaphore s_hIn, s_oIn;
    Semaphore s_hBarrier, s_oBarrier;

public:
    H2O1() : s_hIn{2}, s_oIn{1}, s_hBarrier{0}, s_oBarrier{0} {}

    void hydrogen(function<void()> releaseHydrogen)
    {
        s_hIn.wait(); // 已经有 2 个 H 了，阻塞
        s_oBarrier.signal();
        s_hBarrier.wait();
        releaseHydrogen();
        s_hIn.signal(); // 释放
    }

    void oxygen(function<void()> releaseOxygen)
    {
        s_oIn.wait(); // 已经有 1 个 O 了，阻塞
        s_oBarrier.wait();
        s_oBarrier.wait();
        s_hBarrier.signal();
        s_hBarrier.signal();
        releaseOxygen();
        s_oIn.signal(); // 释放
    }
};