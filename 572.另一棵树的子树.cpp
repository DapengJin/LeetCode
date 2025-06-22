#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=572 lang=cpp
 *
 * [572] 另一棵树的子树
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
    // 代码逻辑同 104. 二叉树的最大深度
    int getHeight(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        int left_h = getHeight(root->left);
        int right_h = getHeight(root->right);

        return max(left_h, right_h) + 1;
    }

    // 100. 相同的树
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr || q == nullptr)
            return p == q; // 必须都是 nullptr

        return p->val == q->val &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }

public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        int hs = getHeight(subRoot);

        // 返回 node 的高度，以及是否找到了 subRoot
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> pair<int, bool>
        {
            if (node == nullptr)
                return {0, false};

            auto [left_h, left_found] = dfs(node->left);
            auto [right_h, right_found] = dfs(node->right);

            if (left_found || right_found)
                return {0, true};

            int node_h = max(left_h, right_h) + 1;

            return {node_h, node_h == hs && isSameTree(node, subRoot)};
        };
        
        return dfs(root).second;
    }
};
// @lc code=end
