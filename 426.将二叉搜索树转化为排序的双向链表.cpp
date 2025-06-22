#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=426 lang=cpp
 *
 * [426] 将二叉搜索树转化为排序的双向链表
 */

// @lc code=start
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr) return root; 
        
        // left  pre
        // right suc
        Node dummy(0);
        stack<Node*> path; 

        while (root)
        { 
            path.push(root); 

            root= root->left; 
        }

        auto cur = &dummy; 

        while (path.size())
        { 
            auto node = path.top(); path.pop(); 

            cur->right = node; 
            node->left = cur; 
            cur = cur->right; 

            if (node->right) 
            {
                node = node->right; 

                while (node)
                { 
                    path.push(node);
                    node = node->left; 
                }
            }
        }

        cur->right = dummy.right; 
        dummy.right->left = cur; 

        return dummy.right; 
    }
};
// @lc code=end

