#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=998 lang=cpp
 *
 * [998] 最大二叉树 II
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
class Solution
{
public:
    TreeNode *insertIntoMaxTree(TreeNode *root, int val)
    {
        if (root == nullptr)
            return new TreeNode(val);

        // 因为 val 是 construct 里最后一个，且大于 root (==最大)
        // 所以 root 在 val 左边，右边为 空
        if (root->val < val)
        {
            auto new_node = new TreeNode(val);
            new_node->left = root; 
            return new_node; 
        }
        
        // val 是最后一个， val 肯定在 root 右边
        root->right = insertIntoMaxTree(root->right, val);

        return root; 
    }
};
// @lc code=end
