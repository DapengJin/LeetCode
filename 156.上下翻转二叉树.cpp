#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=156 lang=cpp
 *
 * [156] 上下翻转二叉树

给你一个二叉树的根节点 root ，请你将此二叉树上下翻转，并返回新的根节点。

你可以按下面的步骤翻转一棵二叉树：

原来的左子节点变成新的根节点
原来的根节点变成新的右子节点
原来的右子节点变成新的左子节点

上面的步骤逐层进行。题目数据保证每个右节点都有一个同级节点（即共享同一父节点的左节点）且不存在子节点。

 

示例 1：

         1
        / \
       2   3
      / \
     4   5

         4
        / \
       5   2
          / \
         3   1

输入：root = [1,2,3,4,5]
输出：[4,5,2,null,null,3,1]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]
 

提示：

树中节点数目在范围 [0, 10] 内
1 <= Node.val <= 10
树中的每个右节点都有一个同级节点（即共享同一父节点的左节点）
树中的每个右节点都没有子节点
 */

// @lc code=start
class Solution
{
    using TN = TreeNode;

public:
    TreeNode *upsideDownBinaryTree(TreeNode *root)
    {
        // 定义一个递归函数 dfs，接受当前节点 node，父节点 p，右兄弟 s
        function<TN *(TN *, TN *, TN *)> dfs =
            [&](TN *node, TN *p, TN *s) -> TN *
        {
            if (node == nullptr)
                return p; // 递归到底，返回新根节点（原来的最左节点）

            // 向下递归，找到新root，并且传递上来
            auto root = dfs(node->left, node, node->right);

            // 当前节点翻转：左指针指向原右兄弟，右指针指向原父节点
            node->left = s;
            node->right = p;

            return root;
        };

        // 注意 root 也会被翻转， 把 它的 left right 设为 nullptr
        // 因为这里的 p 和 s 入参是 nullptr
        return dfs(root, nullptr, nullptr);
    }
};
// @lc code=end

class Solution
{
    using TN = TreeNode;

public:
    TreeNode *upsideDownBinaryTree(TreeNode *node)
    {
        // 如果当前节点为空，或者没有左子节点，说明已经到底了
        if (node == nullptr || node->left == nullptr)
            return node;

        // 向下递归，找到新root，并且传递上来
        TN *new_root = upsideDownBinaryTree(node->left);

        // new_node 是当前 node 的左孩子
        TN *new_node = node->left;
        TN *r = node, *l = node->right; // new_node 的左右孩子

        // 当前节点断开原有连接（防止成环）
        node->left = nullptr;
        node->right = nullptr;

        new_node->left = l;
        new_node->right = r;

        return new_root;
    }
};