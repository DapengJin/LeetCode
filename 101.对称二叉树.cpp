#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=101 lang=cpp
 *
 * [101] 对称二叉树
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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p && q) // p，q 都不为空
            return p->val == q->val &&
                   isSameTree(p->left, q->right) &&
                   isSameTree(p->right, q->left);

        return p == q; // p 和 q 都是 nullptr，  return true
                       // p 不为空，q 为空 等情况，return false
    }

    bool isSymmetric(TreeNode *root)
    {
        return isSameTree(root->left, root->right);
    }
};
// @lc code=end
