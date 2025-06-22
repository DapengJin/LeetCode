#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

class Task
{
public:
    time_point<steady_clock> execute_time; // 任务执行时间
    function<void()> func;

    Task(time_point<steady_clock> t, function<void()> f) : execute_time(t), func(f) {}

    bool operator>(const Task &other) const
    {
        return execute_time > other.execute_time; // 小顶堆，最早执行的任务优先
    }
};

class DelayedScheduler
{
private:
    priority_queue<Task, vector<Task>, greater<Task>> queue;
    mutex mtx;
    condition_variable cv;
    bool stop = false;
    thread workerThread;

public:
    DelayedScheduler()
    {
        workerThread = thread([this]()
                              { this->run(); });
    }

    void schedule(long long delay_ms, function<void()> func)
    {
        {
            lock_guard<mutex> lock(mtx);
            auto execute_time = steady_clock::now() + milliseconds(delay_ms);
            queue.push(Task(execute_time, func));
        }
        cv.notify_one(); // 唤醒等待线程
    }

    void run()
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);
            while (queue.empty() && !stop)
            {
                // cv.wait(lock) 自动释放锁 lock，并让当前线程进入等待状态，直到 cv.notify_one() 或 cv.notify_all() 唤醒它
                cv.wait(lock); // 没有任务则等待
            }

            if (stop)
                break;

            auto now = steady_clock::now();
            auto task = queue.top();

            if (task.execute_time > now)
            {
                cv.wait_until(lock, task.execute_time); // 等待到任务执行时间
            }
            else
            {
                queue.pop();
                lock.unlock();
                task.func();
            }
        }
    }

    ~DelayedScheduler()
    {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_one();
        workerThread.join();
    }
};

int main()
{
    DelayedScheduler scheduler;

    auto start = steady_clock::now();

    scheduler.schedule(1000, [start]()
                       { cout << "Task 1 executed at " << duration_cast<milliseconds>(steady_clock::now() - start).count() << " ms" << endl; });

    scheduler.schedule(500, [start]()
                       { cout << "Task 2 executed at " << duration_cast<milliseconds>(steady_clock::now() - start).count() << " ms" << endl; });

    scheduler.schedule(1500, [start]()
                       { cout << "Task 3 executed at " << duration_cast<milliseconds>(steady_clock::now() - start).count() << " ms" << endl; });

    this_thread::sleep_for(chrono::seconds(3)); // 等待任务完成
    return 0;
}
