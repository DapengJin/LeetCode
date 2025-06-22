#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *node1 = head;
        ListNode *node2 = head->next;
        ListNode *node3 = node2->next;

        node1->next = swapPairs(node3); // 1 指向递归返回的链表头
        node2->next = node1;            // 2 指向 1

        return node2; // 返回交换后的链表头节点

        // ListNode dummy(0, head);

        // ListNode *h0 = &dummy;

        // ListNode *pre = nullptr, *cur = h0->next;

        // while (cur && cur->next)
        // {
        //     for (int i = 0; i < 2; i++)
        //     {
        //         ListNode *nxt = cur->next;

        //         cur->next = pre;
        //         pre = cur;
        //         cur = nxt;
        //     }

        //     h0->next->next = cur;
        //     ListNode *tmp = h0->next; // !!! h0->next 变成队尾了
        //     h0->next = pre;
        //     h0 = tmp;
        //     cur = h0->next;
        // }

        // return dummy.next;
    }
};
// @lc code=end
