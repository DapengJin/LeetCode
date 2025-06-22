#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=445 lang=cpp
 *
 * [445] 两数相加 II
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
    ListNode *reverse_recur(ListNode *head)
    {
        // stop
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *new_head = reverse_recur(head->next);

        (head->next)->next = head;
        head->next = nullptr;

        return new_head; // return the last node
    }

    ListNode *addtwo_recur(ListNode *l1, ListNode *l2, int carry = 0)
    {
        if (l1 == nullptr && l2 == nullptr) return carry ? new ListNode(carry) : nullptr;

        if (l1 == nullptr) swap(l1, l2);

        int sum = l1->val + (l2 ? l2->val : 0) + carry;

        l1->val = sum % 10;
        carry = sum / 10;
        l1->next = addtwo_recur(l1->next, l2 ? l2->next : nullptr, carry);

        return l1;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        l1 = reverse_recur(l1); 
        l2 = reverse_recur(l2);

        l1 = addtwo_recur(l1, l2); 
        
        return reverse_recur(l1); 
    }
};
// @lc code=end
