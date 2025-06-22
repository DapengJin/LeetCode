#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=968 lang=cpp
 *
 * [968] 监控二叉树
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
    // the node is monitored by_self, by_child, by_father
    tuple<int, int, int> dfs(TreeNode *node)
    {
        if (node == nullptr)
            return {INT_MAX / 2, 0, 0};

        auto [l_by_self, l_by_child, l_by_father] = dfs(node->left);
        auto [r_by_self, r_by_child, r_by_father] = dfs(node->right);


        int by_father = min(l_by_self, l_by_child) + min(r_by_self, r_by_child);
        // int by_child = min(r_by_self + l_by_self, min(r_by_self + l_by_child, l_by_self + r_by_child));
        // 一定得有一个是 by_self 的，如果都选 by_self 的 （证明 by_self 的都比较小），min 一定是负值，和 0 取 max 就一定是 0
        int by_child = by_father + max(0, min(l_by_self - l_by_child, r_by_self - r_by_child)); 
        // 证明 by_child >= by_father
        // int by_self = min(l_by_self, min(l_by_child, l_by_father)) + min(r_by_self, min(r_by_child, r_by_father)) + 1;
        int by_self = min(l_by_self, l_by_father) + min(r_by_self,r_by_father) + 1;

        return {by_self, by_child, by_father};
    }

public:
    int minCameraCover(TreeNode *root)
    {
        auto [s, c, f] = dfs(root);
        return min(s, c);
    }
};
// @lc code=end
