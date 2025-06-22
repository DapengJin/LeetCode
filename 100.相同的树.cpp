#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=100 lang=cpp
 *
 * [100] 相同的树
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
                   isSameTree(p->left, q->left) &&
                   isSameTree(p->right, q->right);

        return p == q; // p 和 q 都是 nullptr，  return true
                       // p 不为空，q 为空 等情况，return false
    }
};
// @lc code=end
