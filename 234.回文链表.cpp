#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] 回文链表
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
    ListNode* middleNode(ListNode* head) 
    { 
        ListNode *s = head, *f = head; 

        while(f && f->next) 
        {
            s = s->next;
            f = f->next->next;
        }

        return s;
    }

    ListNode* reverse(ListNode *head)
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

    bool isPalindrome(ListNode* head) {
        ListNode *mid = middleNode(head); 
        ListNode *h0  = reverse(mid); 

        while(h0) 
        { 
            if (h0->val != head->val) return false;

            h0   =   h0->next; 
            head = head->next; 
        }

        return true; 
    }
};
// @lc code=end

