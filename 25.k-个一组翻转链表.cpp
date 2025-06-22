#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        // 1 <= k <= n <= 5000
        // we must reverse the first k node
        ListNode dummy(0, head);
        ListNode *fast = &dummy;

        for (int i = 0; i < k; i++)
            fast = fast->next;

        ListNode *h0 = &dummy;

        while (fast)
        {
            ListNode *pre = nullptr, *cur = h0->next; // !!! *cur = h0->next NOT head

            for (int i = 0; i < k; i++)
            {
                if (fast)
                    fast = fast->next;

                ListNode *nxt = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nxt;
            }

            ListNode *new_tail = h0->next; // !!! h0->next is the tail of the revered node
            new_tail->next = cur;          // h0->next->next = cur
            h0->next = pre;                // pre 是 new_head，h0->next 被覆盖
            h0 = new_tail;
        }

        return dummy.next;
    }
};
// @lc code=end
