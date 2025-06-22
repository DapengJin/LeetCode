#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=129 lang=cpp
 *
 * [129] 求根节点到叶节点数字之和
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
    
    int sumNumbers(TreeNode *root)
    {
        int res = 0;   // 所有根-叶路径数字之和
        int num = 0;   // 当前路径组成的数字

        function<void(TreeNode *)> dfs = [&](TreeNode *node)
        {
            // !!! 若在空节点累加 num，num 会被加两次
            if (node == nullptr) return;          // 空结点直接返回

            num = num * 10 + node->val;           // 把当前节点并入路径值

            // 只有左右都为空时才是叶子，才累加
            if (!node->left && !node->right)
                res += num;
            else {
                dfs(node->left);
                dfs(node->right);
            }

            num /= 10;                            // 回溯，去掉本层数位
        };

        dfs(root);
        return res;
    }
};
// @lc code=end
