#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode head;
        ListNode* cur = &head, *a = list1, *b = list2; 

        while (a && b)
        { 
            if (a->val < b->val)
            {
                cur->next = a; 
                cur = cur->next; 
                a = a->next; 
            }
            else
            { 
                cur->next = b; 
                cur = cur->next;
                b = b->next;
            }
        }

        cur->next = a ? a : b; // append the leftovers

        return head.next;
    }
};
// @lc code=end

