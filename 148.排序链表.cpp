#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
 */

// @lc code=start

// 自底向上的归并排序
class Solution
{
    // 获取链表长度
    int getListLength(ListNode *head)
    {
        int length = 0;

        while (head)
        {
            length++;
            head = head->next;
        }

        return length;
    }

    // 分割链表
    // 如果链表长度 <= size，不做任何操作，返回空节点
    // 如果链表长度 > size，把链表的前 size 个节点分割出来（断开连接），并返回剩余链表的头节点
    ListNode *splitList(ListNode *head, int size)
    {
        // 先找到 next_head 的前一个节点
        ListNode *cur = head;

        for (int i = 0; i < size - 1 && cur; i++)
            cur = cur->next;

        // 如果链表长度 <= size
        if (cur == nullptr || cur->next == nullptr)
            return nullptr; // 不做任何操作，返回空节点

        ListNode *next_head = cur->next;
        cur->next = nullptr; // 断开 next_head 的前一个节点和 next_head 的连接

        return next_head;
    }

    // 21. 合并两个有序链表（双指针）
    // 返回合并后的链表的头节点和尾节点
    pair<ListNode *, ListNode *> mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode dummy;         // 用哨兵节点简化代码逻辑
        ListNode *cur = &dummy; // cur 指向新链表的末尾

        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                cur->next = list1; // 把 list1 加到新链表中
                list1 = list1->next;
            }
            else
            {                      // 注：相等的情况加哪个节点都是可以的
                cur->next = list2; // 把 list2 加到新链表中
                list2 = list2->next;
            }
            cur = cur->next;
        }

        cur->next = list1 ? list1 : list2; // 拼接剩余链表

        while (cur->next)
            cur = cur->next;

        // 循环结束后，cur 是合并后的链表的尾节点
        return {dummy.next, cur};
    }

public:
    ListNode *sortList(ListNode *head)
    {
        int length = getListLength(head); // 获取链表长度

        ListNode dummy(0, head);          // 用哨兵节点简化代码逻辑

        // step 为步长，即参与合并的链表长度
        for (int step = 1; step < length; step *= 2)
        {
            ListNode *new_list_tail = &dummy; // 新链表的末尾
            ListNode *cur = dummy.next;       // 每轮循环的起始节点

            while (cur)
            {
                // 从 cur 开始，分割出两段长为 step 的链表，头节点分别为 head1 和 head2
                ListNode *head1 = cur;
                ListNode *head2 = splitList(head1, step);

                cur = splitList(head2, step); // 下一轮循环的起始节点
                
                // 合并两段长为 step 的链表
                auto [head, tail] = mergeTwoLists(head1, head2);
                // 合并后的头节点 head，插到 new_list_tail 的后面
                new_list_tail->next = head;
                new_list_tail = tail; // tail 现在是新链表的末尾
            }
        }

        return dummy.next;
    }
};
// @lc code=end

/**
 * merge sort
 *
 * time  O(n * logn)
 * space O(    logn)
 *
 */
class Solution
{
    // 找链表中点（快慢指针法）并断开前半部分
    ListNode *middle_node(ListNode *head)
    {
        auto fast = head, slow = head, pre = head;

        while (fast && fast->next)
        {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // 断开链表为两半（左：head ~ pre，右：slow ~ end）
        pre->next = nullptr;

        return slow; // 返回右半部分的头结点
    }

    // 合并两个有序链表（标准双指针）
    ListNode *mergeTwoLists(ListNode *a, ListNode *b)
    {
        ListNode dummy; // 哨兵节点，简化边界处理
        auto cur = &dummy;

        while (a && b)
        {
            if (a->val < b->val)
            {
                cur->next = a;
                a = a->next;
            }
            else
            {
                cur->next = b;
                b = b->next;
            }

            cur = cur->next;
        }

        // 拼接剩余部分
        cur->next = a ? a : b;

        return dummy.next;
    }

public:
    ListNode *sortList(ListNode *head)
    {
        // stop condition, at least one node
        if (head == nullptr || head->next == nullptr)
            return head;

        auto mid = middle_node(head); // head and mid

        auto a = sortList(head);
        auto b = sortList(mid);

        return mergeTwoLists(a, b);
    }
};

/**
 * bubble sort
 *
 * time  O(n*n)
 * space O(1)
 *
 */
class Solution_bubble_sort
{
public:
    ListNode *sortList(ListNode *head)
    {
        int n = 0;
        auto cur = head;

        // get the length
        while (cur)
        {
            n++;
            cur = cur->next;
        }

        // bubble sort
        for (int i = 0; i < n - 1; i++) // the last one don't need to be sorted
        {                               // the biggest element will be swapped to the last position
            bool swapped = false;
            cur = head;

            for (int j = 0; j < n - i - 1; j++) // n - i is sorted
            {
                if (cur->val > cur->next->val)
                {
                    swap(cur->val, cur->next->val);
                    swapped = true;
                }

                cur = cur->next;
            }

            if (swapped == false)
                break;
        }

        return head;
    }
};