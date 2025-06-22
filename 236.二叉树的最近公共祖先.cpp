#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
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
    TreeNode *lowestCommonAncestor(TreeNode *node, TreeNode *p, TreeNode *q)
    {
        if (node == nullptr)
            return node;

        // 设当前节点是 p，不管 p 的子孙 是否有 q, 都可直接返回 p 不用在进行遍历
        if (node == p || node == q) 
            return node;

        TreeNode *l = lowestCommonAncestor(node->left , p, q); 
        TreeNode *r = lowestCommonAncestor(node->right, p, q);

        if (l && r) return node; 
        // else if (l || r) return l ? l : r; 
        // else return nullptr; 

        return l ? l : r; // r 不是p，q 就是 nullptr
    }
};
// @lc code=end
