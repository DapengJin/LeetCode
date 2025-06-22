#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2816 lang=cpp
 *
 * [2816] 翻倍以链表形式表示的数字
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
    ListNode* reverse(ListNode *head)
    { 
        if (head == nullptr || head->next == nullptr) return head; 

        ListNode * new_head = reverse(head->next); 

        head->next->next = head; 
        head->next = nullptr; 

        return new_head;
    }

    ListNode* double_(ListNode* head, int carry = 0) 
    { 
        if (head == nullptr) return carry ? new ListNode(carry) : nullptr; 

        int sum = head->val * 2 + carry; 

        head->val = sum % 10; 
        carry = sum / 10; 
        head->next = double_(head->next, carry); 
        
        return head;
    }
    ListNode* doubleIt(ListNode* head) {
        head = reverse(head); 
        head = double_(head); 

        return reverse(head); 
    }
};
// @lc code=end

