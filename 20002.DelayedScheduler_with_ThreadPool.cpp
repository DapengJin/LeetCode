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
    function<void()> func;                 // 任务执行的回调函数

    Task(time_point<steady_clock> t, function<void()> f) : execute_time(t), func(f) {}

    bool operator>(const Task &other) const
    {
        return execute_time > other.execute_time; // 小顶堆，最早执行的任务优先
    }
};

// 线程池类：用于并发执行任务
class ThreadPool
{
private:
    vector<thread> workers;        // 线程池中的工作线程
    queue<function<void()>> tasks; // 任务队列
    mutex mtx;                     // 互斥锁，保护任务队列
    condition_variable cv;         // 条件变量，用于线程间同步
    bool stop = false;             // 线程池是否停止

public:
    // 构造函数，创建指定数量的线程
    ThreadPool(size_t thread_count)
    {
        for (size_t i = 0; i < thread_count; ++i)
        {
            workers.emplace_back([this]()
                                 {
                while (true) {
                    function<void()> task;

                    {
                        unique_lock<mutex> lock(mtx);

                        // 等待任务到来，或者线程池停止
                        // cv.wait(lock, predicate) 是条件变量的带谓词（predicate）版本。
                        // predicate true 执行
                        cv.wait(lock, [this] { return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) return;  // 线程池停止后退出
                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    task(); // 执行任务
                } });
        }
    }

    // 将新任务加入线程池
    void enqueue(function<void()> task)
    {
        {
            lock_guard<mutex> lock(mtx);
            tasks.push(std::move(task));
        }
        cv.notify_one(); // 唤醒一个线程执行任务
    }

    ~ThreadPool()
    {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all(); // 唤醒所有线程，确保它们可以安全退出
        for (thread &worker : workers)
            worker.join(); // 等待所有线程结束
    }
};

// 延迟调度器：调度任务，并将它们分配到线程池
class DelayedScheduler
{
private:
    priority_queue<Task, vector<Task>, greater<Task>> queue; // 任务优先队列（小顶堆）
    mutex mtx;                                               // 互斥锁，保护任务队列
    condition_variable cv;                                   // 条件变量，唤醒调度线程
    bool stop = false;                                       // 标志调度器是否停止
    thread schedulerThread;                                  // 调度线程
    ThreadPool threadPool;                                   // 线程池

public:
    // 初始化调度器，创建调度线程
    DelayedScheduler(size_t thread_count = 4) : threadPool(thread_count)
    {
        schedulerThread = thread([this]()
                                 { this->run(); });
    }

    // 调度任务，延迟执行
    void schedule(long long delay_ms, function<void()> func)
    {
        {
            lock_guard<mutex> lock(mtx);
            auto execute_time = steady_clock::now() + milliseconds(delay_ms);
            queue.push(Task(execute_time, func));
        }
        cv.notify_one(); // 唤醒调度线程
    }

    // 任务调度逻辑（在单独的调度线程中运行）
    void run()
    {
        while (true)
        {
            unique_lock<mutex> lock(mtx);

            // 如果队列为空，则等待新的任务
            cv.wait(lock, [this]
                    { return stop || queue.size(); });

            if (stop)
                break;

            auto now = steady_clock::now();
            auto task = queue.top();

            if (task.execute_time > now)
                // 任务尚未到达执行时间，等待到达执行时间
                cv.wait_until(lock, task.execute_time);
            else
            {
                queue.pop();                   // 任务时间已到，取出任务
                lock.unlock();                 // 释放锁，避免不必要的锁竞争
                threadPool.enqueue(task.func); // 提交到线程池
            }
        }
    }

    // 析构函数，安全停止调度器
    ~DelayedScheduler()
    {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }

        cv.notify_one();        // 唤醒调度线程，以便它可以安全退出
        schedulerThread.join(); // 等待调度线程退出
    }
};

int main()
{
    DelayedScheduler scheduler(4); // 4 线程的线程池

    auto start = steady_clock::now();

    // 任务 1：延迟 1000ms 执行，执行时间 2s
    scheduler.schedule(1000, [start]()
                       {
                           cout << "Task 1 executing at "
                                << duration_cast<milliseconds>(steady_clock::now() - start).count()
                                << " ms" << endl;
                           this_thread::sleep_for(seconds(2)); // 模拟耗时任务
                           cout << "Task 1 executed at "
                           << duration_cast<milliseconds>(steady_clock::now() - start).count()
                           << " ms" << endl; });

    // 任务 2：延迟 500ms 执行
    scheduler.schedule(500, [start]()
                       { cout << "Task 2 executed at "
                              << duration_cast<milliseconds>(steady_clock::now() - start).count()
                              << " ms" << endl; });

    // 任务 3：延迟 1500ms 执行
    scheduler.schedule(1500, [start]()
                       { cout << "Task 3 executed at "
                              << duration_cast<milliseconds>(steady_clock::now() - start).count()
                              << " ms" << endl; });

    this_thread::sleep_for(chrono::seconds(5)); // 等待任务执行完成
    return 0;
}