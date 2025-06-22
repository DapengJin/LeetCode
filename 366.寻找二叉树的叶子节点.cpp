#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=366 lang=cpp
 *
 * [366] 寻找二叉树的叶子节点
 *
 * 给你一棵二叉树的 root 节点，请按照以下方式收集树的节点：

收集所有的叶子节点。
移除所有的叶子节点。
重复以上步骤，直到树为空。


示例 1：


输入：root = [1,2,3,4,5]
输出：[[4,5,3],[2],[1]]
解释：
[[3,5,4],[2],[1]] 和 [[3,4,5],[2],[1]] 也被视作正确答案，因为每一层返回元素的顺序不影响结果。
示例 2：

输入：root = [1]
输出：[[1]]


提示：

树中节点的数量在[1, 100]范围内。
-100 <= Node.val <= 100
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
    vector<vector<int>> findLeaves(TreeNode *root)
    {
        vector<vector<int>> res;
        vector<int> level;

        function<int(TreeNode *)> dfs = [&](TreeNode *node) -> int
        {
            if (node == nullptr) return -1; // 叶子节点 是 0

            int left  = dfs(node->left);  // left 是叶子，刚开始就被删掉了
            int right = dfs(node->right); // right 很长，到很后面才会被删掉

            int level = max(left, right) + 1; // 先把 right 下面长的都删完 才能删 当前节点

            if (level == res.size()) res.push_back({}); // res 长度不够添加 level

            res[level].push_back(node->val);

            return level;
        };

        dfs(root);

        return res;
    }
};
// @lc code=end
/* 真 删除 */
class Solution
{
public:
    vector<vector<int>> findLeaves(TreeNode *root)
    {
        vector<vector<int>> res;
        vector<int> level;

        function<bool(TreeNode *)> dfs = [&](TreeNode *node) -> bool
        {
            if (node->left == node->right)
            {
                level.push_back(node->val);
                return true;
            }

            if (node->left && dfs(node->left))
            {
                auto tmp = node->left;
                node->left = nullptr;
                // delete tmp;
            }

            if (node->right && dfs(node->right))
            {
                auto tmp = node->right;
                node->right = nullptr;
                // delete tmp;
            }

            return false;
        };

        TreeNode dummy;
        TreeNode *head = &dummy;
        head->left = root;

        while (head->left)
        {
            level = {};
            dfs(head);
            res.push_back(level);
        }

        return res;
    }
};