#include "pkgs.h" 
/*
 * @lc app=leetcode.cn id=938 lang=cpp
 *
 * [938] 二叉搜索树的范围和
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
    int rangeSumBST(TreeNode *root, int low, int high)
    {
        if (root == nullptr)
            return 0;

        int x = root->val;

        if (x > high) // 右子树没有节点在范围内，只需递归左子树
            return rangeSumBST(root->left, low, high);

        if (x < low)  // 左子树没有节点在范围内，只需递归右子树
            return rangeSumBST(root->right, low, high);

        return x + rangeSumBST(root->left, low, high) +
                   rangeSumBST(root->right, low, high);
    }
};
// @lc code=end
