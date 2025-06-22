#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */

// @lc code=start
class MyQueue
{
    stack<int> s1, s2;

    // 辅助函数：将 s1 中的所有元素倒入 s2
    void dump_s1()
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
    }

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        s1.push(x);
    }

    int pop()
    {
        if (s2.empty()) // 只有当 s2 为空时，才需要倾倒元素
        {
            dump_s1();
        }

        int res = s2.top();
        s2.pop();

        return res;
    }

    int peek()
    {
        if (s2.empty()) // 只有当 s2 为空时，才需要倾倒元素
        {
            dump_s1();
        }

        return s2.top();
    }

    bool empty()
    {
        return s1.empty() && s2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end
