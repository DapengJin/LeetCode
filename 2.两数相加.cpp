#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2, int carry = 0)
    {
        /* 方法一：递归 */
        // 如果进位了，就额外创建一个节点
        if (!l1 && !l2)    return carry ? new ListNode(carry) : nullptr;

        if (l1 == nullptr) swap(l1, l2); // 保证 l1 不为空

        int sum = carry + l1->val + (l2 ? l2->val : 0);

        l1->val = sum % 10;
        carry = sum / 10;

        // !!! l2 可能是 nullptr
        l1->next = addTwoNumbers(l1->next, l2 ? l2->next : nullptr, carry);

        return l1;

        /* 方法二：迭代 */
        // ListNode dummy;
        // ListNode *cur = &dummy;
        // int carry = 0;

        // while (l1 || l2 || carry)
        // {
        //     if (l1)
        //     {
        //         carry += l1->val;
        //         l1 = l1->next;
        //     }

        //     if (l2)
        //     {
        //         carry += l2->val;
        //         l2 = l2->next;
        //     }

        //     cur = cur->next = new ListNode(carry % 10);
        //     carry /= 10;
        // }

        // return dummy.next;
    }
};
// @lc code=end
