#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=510 lang=cpp
 *
 * [510] 二叉搜索树中的中序后继 II
 *
 * 给定一棵二叉搜索树和其中的一个节点 node ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。

一个节点 node 的中序后继是键值比 node.val 大所有的节点中键值最小的那个。

你可以直接访问结点，但无法直接访问树。每个节点都会有其父节点的引用。节点 Node 定义如下：

class Node {
    public int val;
    public Node left;
    public Node right;
    public Node parent;
}


示例 1：



输入：tree = [2,1,3], node = 1
输出：2
解析：1 的中序后继结点是 2 。注意节点和返回值都是 Node 类型的。
示例 2：



输入：tree = [5,3,6,2,4,null,null,1], node = 6
输出：null
解析：该结点没有中序后继，因此返回 null 。


提示：

树中节点的数目在范围 [1, 104] 内。
-105 <= Node.val <= 105
树中各结点的值均保证唯一。


进阶：你能否在不访问任何结点的值的情况下解决问题?
 */
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *parent;
};

// @lc code=start
class Solution
{
public:
    Node *inorderSuccessor(Node *node)
    {
        /**
         * case 1: 节点有右子树
         * 
         *      node
         *          \
         *           right
         *          /
         *        left 
         *        /
         *      left
         *      /
         *    left    (left 还是大于 node 的)
         * 
         * 中序遍历的后继是右子树中最左边的节点
         */
        if (node->right)
        {
            node = node->right;

            while (node->left)
                node = node->left;

            return node;
        }

        /**
         * case 2: 节点没有右子树
         * 
         * 要找的是第一个「把当前节点当作左子树」的祖先
         * 
         * 比如这种情况：
         * 
         *         parent
         *         /
         *     parent
         *          \
         *        parent
         *            \
         *          parent
         *              \
         *              node   <-- 当前节点
         * 
         * 向上找，5 是 4 的右孩子，4 是 3 的右孩子，一直到 3 是 6 的左孩子，说明 6 是第一个比当前节点大的祖先
         * 
         * 所以我们需要一直往上爬，直到遇到某个祖先节点，它把当前节点作为左孩子
         */
        // 循环到 节点为空 （把 当前节点当右孩子 的节点）
        while (node->parent && node->parent->right == node)
            node = node->parent;

        return node->parent; // 只能是 把 当前节点当左孩子 节点 或 nullptr
    }
};
// @lc code=end
