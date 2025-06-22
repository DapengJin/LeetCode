#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
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
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *f = head, *s = head;

        while (f && f->next)
        {
            s = s->next;
            f = f->next->next;

            if (f == s)
            {
                while (s != head)
                {
                    s = s->next; 
                    head = head->next;
                }

                return head;
            }
        }

        return nullptr;

        // ListNode *fast = head, *slow = head;

        // // !!! at the begining, fast == slow == head. cannot do this
        // // while (fast != slow)
        // // {
        // //     ...
        // // }

        // do {
        //     // no circle
        //     if (fast == nullptr || fast->next == nullptr)
        //         return nullptr;

        //     fast = fast->next->next;
        //     slow = slow->next;
        // } while (fast != slow);

        // // fast == slow now
        // fast = head;

        // while (fast != slow) {
        //     fast = fast->next;
        //     slow = slow->next;
        // }

        // return fast;
    }
};
// @lc code=end
