#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=257 lang=cpp
 *
 * [257] 二叉树的所有路径
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res; 
        // string path; // !!! 用全局的 path 不好 pop 

        function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path)
        { 
            if (node == nullptr) return;

            path += to_string(node->val);
            
            if (node->left == node->right) // nullptr
            {
                res.push_back(path);
                return; 
            }

            path += "->"; 

            dfs(node->left, path);
            dfs(node->right, path);
        };

        dfs(root, ""); 
        
        return res; 
    }
};
// @lc code=end

