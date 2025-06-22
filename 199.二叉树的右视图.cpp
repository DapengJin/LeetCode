#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=199 lang=cpp
 *
 * [199] 二叉树的右视图
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res; 
        // 记录目前已访问的最大深度
        int h_max = 0; // 或者直接看 res 的长度也行

        // 节点 root 和 当前深度 height
        function<void(TreeNode *, int)> recur = [&](TreeNode *root, int height = 1) -> void
        {
            if (root == nullptr) return; 

            // 如果第一次到达这个深度，就把节点值加入结果
            if (height > h_max) 
            {
                res.push_back(root->val); 
                h_max = height;
            }

            // 先遍历右子树，保证右侧节点优先被访问
            recur(root->right, height + 1); 
            recur(root->left,  height + 1); 
        }; 

        recur(root, 1); 

        return res; 
    }
};
// @lc code=end

