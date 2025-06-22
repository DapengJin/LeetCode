#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=671 lang=cpp
 *
 * [671] 二叉树中第二小的节点
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
    int findSecondMinimumValue(TreeNode *root)
    {
        int root_val = root->val; // 第一小肯定是 root->val
        int res = -1;

        function<void(TreeNode *)> dfs = [&](TreeNode *node)
        {
            if (node == nullptr)
                return;

            if (node->val != root_val) // 不等于 第一小
            {
                // node->val 可能是第二小
                if (res == -1 || res > node->val)
                    res = node->val;

                // 可以提前返回（它的孩子都不可能 小于 它）
                return;
            }

            dfs(node->left);
            dfs(node->right);

            return;
        };

        dfs(root);

        return res;
    }
};
// @lc code=end
