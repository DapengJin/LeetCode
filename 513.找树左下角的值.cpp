#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=513 lang=cpp
 *
 * [513] 找树左下角的值
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    public:
        int findBottomLeftValue(TreeNode* root) {
            queue<TreeNode *> q; 
            TreeNode *node = nullptr;
            
            q.push(root); 
            
            while (!q.empty())
            {
                node = q.front(); 
                q.pop(); 
                
                if (node->right) q.push(node->right); 
                if (node->left ) q.push(node->left); 
            }
            
            return node->val; 
            
        }
    };
// @lc code=end

