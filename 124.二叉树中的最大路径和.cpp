#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=124 lang=cpp
 *
 * [124] 二叉树中的最大路径和
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
    int maxPathSum(TreeNode *root)
    {
        int res = INT_MIN;

        function<int(TreeNode *)> dfs = [&](TreeNode *root) -> int
        {
            if (root == nullptr)
                return 0;

            int l_val = dfs(root->left);
            int r_val = dfs(root->right);

            res = max(res, root->val + l_val + r_val);

            return max(max(l_val, r_val) + root->val, 0); // !!! max(___, 0); 
        };

        dfs(root);

        return res;
    }
};
// @lc code=end
