#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
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
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        auto cmp = [](ListNode *a, ListNode *b) -> bool
        {
            return a->val > b->val;
        };

        priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> q;

        for (auto l : lists)
            if (l)
                q.push(l);

        ListNode dummy, *cur = &dummy;

        while (q.size())
        {
            ListNode *node = q.top();
            q.pop();

            cur->next = node;
            cur = cur->next;

            if (node->next)
                q.push(node->next);
        }

        return dummy.next;
    }
};

// @lc code=end
