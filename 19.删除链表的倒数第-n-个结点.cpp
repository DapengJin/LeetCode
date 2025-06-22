#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
    int recur(ListNode *head, int n)
    {
        if (head->next == nullptr)
            return 1;

        int count = recur(head->next, n) + 1;

        if (count == n + 1)
        {
            head->next = head->next->next;
        }

        return count;
    }
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        /* 快慢指针 */
        // 由于可能会删除链表头部，用哨兵节点简化代码
        ListNode dummy{0, head};
        ListNode *left = &dummy;
        ListNode *right = &dummy;
        while (n--)
        {
            right = right->next; // 右指针先向右走 n 步
        }
        while (right->next)
        {
            left = left->next;
            right = right->next; // 左右指针一起走
        }
        // 左指针的下一个节点就是倒数第 n 个节点
        ListNode *nxt = left->next;
        left->next = left->next->next;
        delete nxt;
        return dummy.next;

        /* 递归 */
        // ListNode dummy(0, head);

        // recur(&dummy, n);

        // return dummy.next;
    }
};
// @lc code=end
