#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=141 lang=cpp
 *
 * [141] 环形链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *f = head, *s = head;

        while (f && f->next)
        {
            s = s->next;
            f = f->next->next;

            if (f == s) return true;
        }

        return false;
    }
};
// @lc code=end
