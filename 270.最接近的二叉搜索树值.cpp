#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=270 lang=cpp
 *
 * [270] 最接近的二叉搜索树值
 *
 *
给你二叉搜索树的根节点 root 和一个目标值 target ，请在该二叉搜索树中找到最接近目标值 target 的数值。如果有多个答案，返回最小的那个。


示例 1：

          4
         / \
        2   5
       / \
      1   3
输入：root = [4,2,5,1,3], target = 3.714286
输出：4
示例 2：

输入：root = [1], target = 4.428571
输出：1


提示：

树中节点的数目在范围 [1, 104] 内
0 <= Node.val <= 109
-109 <= target <= 109


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
    int closestValue(TreeNode *root, double target)
    {
        int res = root->val;
        auto cur = root;

        while (cur)
        {
            double cur_diff = abs(cur->val - target);
            double res_diff = abs(res - target);

            // 如果当前节点更接近目标，则更新 res
            if (res_diff > cur_diff)
                res = cur->val;
            // 如果两者一样接近，取较小的值
            else if (res_diff == cur_diff)
                res = res > cur->val ? cur->val : res;

            if (cur->val < target)
                cur = cur->right; // 目标更大，往右子树找
            else if (cur->val == target)
                return cur->val;
            else
                cur = cur->left;  // 目标更小，往左子树找
        }

        return res;
    }
};
// @lc code=end
class Solution
{
public:
    // 找到 BST 中最接近 target 的节点值
    int closestValue(TreeNode *root, double target)
    {
        int res = 0;           // 记录当前最接近的节点值
        double diff = DBL_MAX; // 记录当前最小的绝对差

        // 利用 BST 的性质做递归搜索
        function<void(TreeNode *)> dfs = [&](TreeNode *node)
        {
            if (node == nullptr) return; // 遇到空节点直接返回

            // 计算当前节点值与 target 的差距
            double curDiff = fabs(target - node->val);

            if (curDiff < diff ||                     // 如果当前差距更小，或
                (curDiff == diff && node->val < res)) //差距相等但节点值更小，则更新结果
            {
                res = node->val;
                diff = curDiff;
            }

            // BST 特性：target 比当前节点值大，就到右子树；否则到左子树
            if (target > node->val) dfs(node->right);
            else dfs(node->left);
        };

        dfs(root); // 从根节点开始 DFS
        return res;
    }
};