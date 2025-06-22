#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=876 lang=cpp
 *
 * [876] 链表的中间结点
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
    ListNode *middleNode(ListNode *head)
    {
        ListNode *s = head, *f = head;

        while (f && f->next)
        {
            s = s->next;
            f = f->next->next;
        }

        return s;

        // // head is not nullptr (链表的结点数范围是 [1, 100])
        // ListNode *s = head, *f = head->next;

        // while (f)
        // {
        //     s = s->next;
        //     f = f->next ? f->next->next : f->next; // f->next->next 可能为 nullptr
        // }

        // return s;
    }
};
// @lc code=end
