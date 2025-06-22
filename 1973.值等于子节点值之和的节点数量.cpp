#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1973 lang=cpp
 *
 * [1973] 值等于子节点值之和的节点数量
给定一颗二叉树的根节点 root ，返回满足条件：节点的值等于该节点所有子节点的值之和 的节点的数量。

一个节点 x 的 子节点 是指从节点 x 出发，到所有叶子节点路径上的节点。没有子节点的节点的子节点和视为 0 。

 

示例 1:
      10
     /  \
    3    4
   / \
  2   1

输入: root = [10,3,4,2,1]
输出: 2
解释:
对于值为10的节点: 其子节点之和为： 3+4+2+1 = 10。
对于值为3的节点：其子节点之和为： 2+1 = 3。
示例 2:


输入: root = [2,3,null,2,null]
输出: 0
解释:
没有节点满足其值等于子节点之和。
示例 3:


输入: root = [0]
输出: 1
解释:
对于值为0的节点：因为它没有子节点，所以自己点之和为0。
 

提示：

树中节点的数量范围： [1, 105]
0 <= Node.val <= 105
 */

// @lc code=start
class Solution {
public:
    int equalToDescendants(TreeNode* root) {
        int res = 0; 

        auto dfs = [&](this auto &&dfs, TreeNode* node) -> long // sum of the sub-tree
        { 
            if (node == nullptr) return 0; 

            int s = dfs(node->left) + dfs(node->right); 

            if (s == node->val) res++; 

            return node->val + s; 
        };

        dfs(root); 

        return res; 
    }
};
// @lc code=end

