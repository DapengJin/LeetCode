#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=113 lang=cpp
 *
 * [113] 路径总和 II
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
    vector<vector<int>> pathSum(TreeNode *root, int targetSum)
    {
        vector<vector<int>> res;
        vector<int> path;

        function<void(TreeNode *, int)> dfs = [&](TreeNode *node, int sum)
        {
            if (node == nullptr)
                return; // !!! 在这 res.push_back(path); 就会被计算两次

            sum += node->val;
            path.push_back(node->val);

            // node->left == node->right 相当于判断左右节点是否均为 nullptr
            // 判断是否为叶子节点（左右子节点都为空）
            if (node->left == node->right)
            {
                // 如果路径和正好等于 targetSum，记录当前路径
                if (sum == targetSum)
                    res.push_back(path);
            }
            // 不是叶子，继续向下遍历左右子树
            // 注意不能提前根据 sum < targetSum 剪枝，因为 node->val 可能为负数
            else
            {
                dfs(node->left, sum);
                dfs(node->right, sum);
            }

            path.pop_back();
        };

        dfs(root, 0);

        return res;
    }
};
// @lc code=end
