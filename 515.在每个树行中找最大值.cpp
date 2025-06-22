#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=515 lang=cpp
 *
 * [515] 在每个树行中找最大值
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
    vector<int> largestValues(TreeNode *root)
    {
        if (root == nullptr) return {}; 

        queue<TreeNode *> q;
        q.push(root);
        vector<int> res;

        while (q.size())
        {
            // level
            int n = q.size();
            int level_max = INT_MIN;

            for (int i = 0; i < n; i++)
            {
                auto node = q.front();
                q.pop();

                level_max = max(level_max, node->val);

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            res.push_back(level_max);
        }

        return res;
    }
};
// @lc code=end
