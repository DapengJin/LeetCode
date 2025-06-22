#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2130 lang=cpp
 *
 * [2130] 链表最大孪生和
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

    int pairSum(ListNode* head) {
        ListNode *mid = middleNode(head); 
        
        mid = reverse(mid); 

        int res = 0; 

        while (mid)
        {
            res = max(res, mid->val + head->val); 

            mid  =  mid->next; 
            head = head->next;
        }

        return res;
    }
};
// @lc code=end

