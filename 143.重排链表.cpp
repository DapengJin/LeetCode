#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=143 lang=cpp
 *
 * [143] 重排链表
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
    // [876] 链表的中间结点
    ListNode *middleNode(ListNode *head)
    {
        ListNode *s = head, *f = head;

        while (f && f->next)
        {
            s = s->next;
            f = f->next->next;
        }

        return s;
    }

    // [206] 反转链表
    ListNode *reverseList(ListNode *head)
    {
        ListNode *pre = nullptr, *cur = head;

        while (cur)
        {
            ListNode *nxt = cur->next;

            cur->next = pre;
            pre = cur;
            cur = nxt;
        }

        return pre;
    }

    void reorderList(ListNode *head)
    {
        
        ListNode *mid = middleNode(head); // [1,2,3,4]  [1,2,3,4,5]
        ListNode *h0  = head;             // [1,2,3]    [1,2,3]
        ListNode *h1  = reverseList(mid); // [4,3]      [5,4,3]

        while (h1->next) // !!! 不是 h0 && h1
        { 
            ListNode *h0_nxt = h0->next, *h1_nxt = h1->next;

            h0->next = h1; 

            h1->next = h0_nxt; 

            h0 = h0_nxt; 
            h1 = h1_nxt; 
        }
    }
};
// @lc code=end
