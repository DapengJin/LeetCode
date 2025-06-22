#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1019 lang=cpp
 *
 * [1019] 链表中的下一个更大节点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
    vector<int> ans;
    stack<int> s; // store the value of the node, not index

    void f(ListNode *node, int i)
    {
        if (node == nullptr)
        {
            ans.resize(i); // i 就是链表长度
            return;
        }

        f(node->next, i + 1);

        while (!s.empty() && node->val >= s.top())
            s.pop(); // 弹出无用数据

        if (!s.empty())
            ans[i] = s.top(); // 栈顶就是第 i 个节点的下一个更大元素

        s.push(node->val);
    }

public:
    vector<int> nextLargerNodes(ListNode *head)
    {
        f(head, 0);

        return ans;
    }
};
// @lc code=end
