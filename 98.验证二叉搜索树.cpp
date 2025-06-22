#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
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
    /* 后序遍历 */
    pair<long long, long long> dfs(TreeNode* node) { // 返回的是 当前节点 的范围
        if (node == nullptr) {
            return {LLONG_MAX, LLONG_MIN}; // 空集
        }
        auto[l_min, l_max] = dfs(node->left);
        auto[r_min, r_max] = dfs(node->right);
        long long x = node->val;
        // 也可以在递归完左子树之后立刻判断，如果发现不是二叉搜索树，就不用递归右子树了
        if (x <= l_max || x >= r_min) {
            return {LLONG_MIN, LLONG_MAX}; // 全集
        }
        return {min(l_min, x), max(r_max, x)};
    }

    bool isValidBST(TreeNode* root) {
        return dfs(root).second != LLONG_MAX;
    }

    /* 中序遍历 */
    long long pre = LLONG_MIN;
    bool isValidBST2(TreeNode *root) // !!! pre 不能当做参数，传不过去
    {
        if (root == nullptr)
            return true;

        if (!isValidBST2(root->left)) return false;

        if (root->val <= pre)  return false; 

        pre = root->val;

        return isValidBST2(root->right);  
    }

    /* 前序遍历 */
    bool isValidBST1(TreeNode *root, long long l = LLONG_MIN, long long r = LLONG_MAX)
    {
        if (root == nullptr)
            return true;

        int val = root->val;

        return val > l &&
               val < r &&
               isValidBST1(root->left, l, val) &&
               isValidBST1(root->right, val, r);
    }
};
// @lc code=end
