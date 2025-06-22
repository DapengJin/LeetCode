#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=285 lang=cpp
 *
 * [285] 二叉搜索树中的中序后继
 *
给定一棵二叉搜索树和其中的一个节点 p ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。

节点 p 的后继是值比 p.val 大的节点中键值最小的节点。



示例 1：



输入：root = [2,1,3], p = 1
输出：2
解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
示例 2：



输入：root = [5,3,6,2,4,null,null,1], p = 6
输出：null
解释：因为给出的节点没有中序后继，所以答案就返回 null 了。


提示：

树中节点的数目在范围 [1, 104] 内。
-105 <= Node.val <= 105
树中各节点的值均保证唯一。
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
    {
        // 我们要找的是 值大于 p->val 的最小节点；
        TreeNode *successor = nullptr;

        while (root)
        {
            if (root->val > p->val) // 值大于 p->val
            {
                successor = root;  // 当前节点是一个候选
                root = root->left; // 但也许左子树中还有更小的符合条件的节点，继续往左走
            }
            else
                root = root->right; // 往右走找更大的数
        }

        return successor;
    }
};
// @lc code=end
