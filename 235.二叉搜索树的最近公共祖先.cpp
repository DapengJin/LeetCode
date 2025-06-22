#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=235 lang=cpp
 *
 * [235] 二叉搜索树的最近公共祖先
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        int x = root->val;

        if (p->val < x && q->val < x) // p, q 都在左子树
            return lowestCommonAncestor(root->left, p, q);

        if (p->val > x && q->val > x)
            return lowestCommonAncestor(root->right, p, q);

        return root; // case1: p, q 在不同左右子树
                     // case2: p 或 q 是当前节点
    }
};
// @lc code=end
class Solution1
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr ||
            root->val == p->val || // 找到其中一个直接返回
            root->val == q->val)
            return root;

        if (p->val > q->val)
            swap(p, q); // 确保 p 是小的

        if (root->val > p->val && root->val < q->val) // 分叉 答案就是 root
            return root;
        // 都在右边
        else if (p->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        // 都在左边
        else
            return lowestCommonAncestor(root->left, p, q);
    }
};