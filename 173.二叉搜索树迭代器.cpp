#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=173 lang=cpp
 *
 * [173] 二叉搜索树迭代器
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
class BSTIterator
{
    // 用一个栈来维护访问路径，模拟中序遍历
    stack<TreeNode *> path;

public:
    BSTIterator(TreeNode *root)
    {
        // 遍历到最左边的节点
        while (root)
        {
            path.push(root);
            root = root->left;
        }
    }

    int next()
    {
        auto node = path.top();
        path.pop();

        int res = node->val;
        
        // 如果当前节点有右子树，则要处理右子树的所有左边路径
        node = node->right;

        while (node)
        {
            path.push(node);
            node = node->left;
        }

        return res;
    }

    bool hasNext()
    {
        return path.size();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
// @lc code=end
