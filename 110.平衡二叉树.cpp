#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=110 lang=cpp
 *
 * [110] 平衡二叉树
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
    bool isBalanced(TreeNode* root) {
        bool res = true; 

        // 优化：返回 -1 代表不平衡，可以提前停止
        function<int(TreeNode *)> h = [&](TreeNode *root) -> int 
        {
            if (root == nullptr) return 0; 

            int left = h(root->left); 
            int right = h(root->right); 

            if (abs(left - right) > 1) res = false; 

            return max(left, right) + 1;
        }; 

        h(root); 

        return res; 
    }
};
// @lc code=end

