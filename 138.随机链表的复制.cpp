#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 随机链表的复制
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node dummy(0); 

        Node *cur_copy = &dummy, *cur = head;
        
        unordered_map<Node*, Node*> m; 


        while (cur) { 
            cur_copy->next = new Node(cur->val); 
            cur_copy = cur_copy->next; 
            m[cur] = cur_copy; 
            cur = cur->next; 
        }

        cur = head; 
        cur_copy = dummy.next; 

        while (cur)
        {
            if (cur->random)
                cur_copy->random = m[cur->random]; 
            
            cur = cur->next; 
            cur_copy = cur_copy->next; 
        }

        return dummy.next; 
        
    }
};
// @lc code=end

