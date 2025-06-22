#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=450 lang=cpp
 *
 * [450] 删除二叉搜索树中的节点
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
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (!root)
            return nullptr; // 终止条件：空树直接返回

        if (key < root->val)
        {
            root->left = deleteNode(root->left, key); // 递归删除左子树
        }
        else if (key > root->val)
        {
            root->right = deleteNode(root->right, key); // 递归删除右子树
        }
        else
        { // 找到要删除的节点
            if (!root->left && !root->right)
            { // 无子节点
                delete root;
                return nullptr;
            }
            if (!root->left || !root->right)
            { // 只有一个子节点
                TreeNode *child = root->left ? root->left : root->right;
                delete root;
                return child;
            }

            // 找到右子树的最小节点（中序后继）
            TreeNode *succ = root->right;
            while (succ->left)
                succ = succ->left;

            root->val = succ->val;                            // 用 successor 值替换 root
            root->right = deleteNode(root->right, succ->val); // 递归删除 successor
        }
        return root;
    }
};
// @lc code=end
