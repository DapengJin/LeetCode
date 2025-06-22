#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=270 lang=cpp
 *
 * [270] 最接近的二叉搜索树值
 *
 *
给定二叉搜索树的根 root 、一个目标值 target 和一个整数 k ，返回BST中最接近目标的 k 个值。你可以按 任意顺序 返回答案。

题目 保证 该二叉搜索树中只会存在一种 k 个值集合最接近 target


示例 1：

          4
         / \
        2   5
       / \
      1   3
输入: root = [4,2,5,1,3]，目标值 = 3.714286，且 k = 2
输出: [4,3]
示例 2:

输入: root = [1], target = 0.000000, k = 1
输出: [1]


提示：

二叉树的节点总数为 n
1 <= k <= n <= 104
0 <= Node.val <= 109
-109 <= target <= 109


进阶：假设该二叉搜索树是平衡的，请问您是否能在小于 O(n)（ n = total nodes ）的时间复杂度内解决该问题呢？

提示 1
Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
提示 2
Try to assume that each node has a parent pointer, it makes the problem much easier.
提示 3
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
提示 4
You would need two stacks to track the path in finding predecessor and successor node separately.


 */

// @lc code=start
/**
 * BST in-order 排序出来的数组是有序的
 *
 * in-order + binary_search + 双指针拓展 O(n + k)
 *
 * 但是题目要求 小于 O(n)
 *
 * getPredecessor(N)
 * getSuccessor(N)
 */
class Solution
{
public:
    vector<int> closestKValues(TreeNode *root, double target, int k)
    {
        vector<int> result;
        stack<TreeNode *> predecessors, successors;

        // 初始化两个栈
        initPredecessorStack(root, target, predecessors);
        initSuccessorStack(root, target, successors);

        // 取 k 个最接近的值
        while (k--)
        {
            if (successors.empty() ||     // 后继节点 为空
                (!predecessors.empty() && // 后继节点/前驱节点 均不为空 && 前驱节点 diff 小一点
                 abs(predecessors.top()->val - target) <= abs(successors.top()->val - target)))
            {
                result.push_back(predecessors.top()->val);
                getNextPredecessor(predecessors);
            }
            else
            {
                result.push_back(successors.top()->val);
                getNextSuccessor(successors);
            }
        }

        return result;
    }

private:
    // 初始化 predecessor 栈：中序方向（左 → 根 → 右）
    // 用 272 做的
    /**
     * init_suc 并没有把所有的后继节点都加进 suc_st，
     *      那它是怎么实现“可以访问所有后继”的呢？
     * 
     * ⸻
     * 
     * ✅ 答案：suc_st 是“访问路径的控制栈”
     * 
     * 它不是一次性把所有后继放进去，而是延迟生成（Lazy Evaluation）！
     * 
     * ⸻
     * 
     * 🎯 suc_st 的作用：
     * 
     * 它保存的是：
     * 
     * 从根到当前后继节点的一条“左路径”，以及未来继续访问后继所需的“上下文信息”。
     * 
     * 通过 suc_st 的栈结构，我们能够在 每次调用 get_suc() 时：
     * 	•	获取当前最近的后继节点；
     * 	•	顺着它的右子树找下一个后继（最左的那个）；
     * 	•	并将这个“路径”压栈，为下一次后继做准备。
     * 
     * ⸻
     * 
     * 🔍 举个例子
     * 
     * 以这棵树为例，target = 4.5：
     * 
     *         5
     *        / \
     *       3   8
     *      / \   \
     *     2   4   10
     * 
     * 初始化 suc_st
     * 
     * 从根开始构建 suc_st：
     * 	•	root = 5 → 5 >= 4.5 → 压栈，往左
     * 	•	3 < 4.5 → 不压栈，往右
     * 	•	4 < 4.5 → 不压栈，往右
     * 	•	nullptr → 停止
     * 
     * 现在：
     * 
     * suc_st: [5] !!! 表示的是 5 和 5 的所有 右子树 节点 ( 如果 target = 3.5: suc_st [5, 4])
     * 
     * 我们只压了一个节点 5，但它是第一个 ≥ target 的节点。我们称它为当前最小的后继。
     * 
     * ⸻
     * 
     * get_suc() 做了什么？
     * 	•	弹出 5（当前后继）
     * 	•	往右走 → node = 8
     * 	•	进入 8 的左路径：
     * 	•	8 → 压栈
     * 	•	8.left == nullptr → 结束
     * 
     * 现在：
     * 
     * suc_st: [8]
     * 
     * 下一个后继就是 8！是不是很妙？✨
     * 我们只在需要时才进入子树，一点点压栈，而不是一次性获取所有后继节点！
     * 
     * ⸻
     * 
     * ✅ 总结一句话：
     * 
     * suc_st 并不是存了“所有后继”，而是存了“如何去找下一个后继”的路径信息。
     * 
     * 同理，pre_st 也是延迟生成前驱节点。
     * 
     * ⸻
     * 
     * 🚀 补充术语
     * 
     * 这种方式在计算机中被称为：
     * 	•	迭代中序遍历（iterative inorder traversal）
     * 	•	惰性求值 / Lazy Evaluation
     * 	•	利用 显式栈模拟递归过程
     * 
     */
    void initPredecessorStack(TreeNode *node, double target, stack<TreeNode *> &stk)
    {
        while (node)
        {
            if (node->val < target)
            {
                stk.push(node);
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }
    }

    // 初始化 successor 栈：反中序方向（右 → 根 → 左）
    void initSuccessorStack(TreeNode *node, double target, stack<TreeNode *> &stk)
    {
        while (node)
        {
            if (node->val >= target)
            {
                stk.push(node);
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
    }

    // 获取前驱（往左子树走，再尽量往右）
    void getNextPredecessor(stack<TreeNode *> &stk)
    {
        TreeNode *node = stk.top();
        stk.pop();
        node = node->left;
        while (node)
        {
            stk.push(node);
            node = node->right;
        }
    }

    // 获取后继（往右子树走，再尽量往左）
    void getNextSuccessor(stack<TreeNode *> &stk)
    {
        TreeNode *node = stk.top();
        stk.pop();
        node = node->right;
        while (node)
        {
            stk.push(node);
            node = node->left;
        }
    }
};
// @lc code=end
/* 用 510 做的 */
// TreeNode *getPrev(unordered_map<TreeNode *, TreeNode *> &parent, TreeNode *cur)
// {
//     // 情况二
//     if (cur->left == nullptr)
//     {
//         while (parent[cur] && parent[cur]->left == cur)
//         {
//             cur = parent[cur];
//         }

//         return cur == NULL ? NULL : parent[cur];
//     }

//     // 情况一
//     parent[cur->left] = cur;
//     cur = cur->left;
//     while (cur->right)
//     {
//         parent[cur->right] = cur;
//         cur = cur->right;
//     }

//     return cur;
// }

// TreeNode *getNext(unordered_map<TreeNode *, TreeNode *> &parent, TreeNode *cur)
// {
//     if (!cur->right)
//     {
//         while (parent[cur] && parent[cur]->right == cur)
//         {
//             cur = parent[cur];
//         }

//         return cur == NULL ? NULL : parent[cur];
//     }

//     parent[cur->right] = cur;
//     cur = cur->right;
//     while (cur->left)
//     {
//         parent[cur->left] = cur;
//         cur = cur->left;
//     }

//     return cur;
// }

// vector<int> closestKValues(TreeNode *root, double target, int k)
// {
//     vector<int> ans;
//     ans.reserve(k);

//     unordered_map<TreeNode *, TreeNode *> parent;
//     parent[root] = NULL;

//     double diff = 10000000;
//     TreeNode *r = root, *closest;
//     while (r)
//     {
//         if (diff > abs(r->val - target))
//         {
//             diff = abs(r->val - target);
//             closest = r;
//         }

//         if (r->val > target)
//         {
//             parent[r->left] = r;
//             r = r->left;
//         }
//         else
//         {
//             parent[r->right] = r;
//             r = r->right;
//         }
//     }

//     ans.push_back(closest->val);

//     TreeNode *smaller = getPrev(parent, closest);
//     TreeNode *bigger = getNext(parent, closest);

//     int i = 1;
//     while (i < k)
//     {
//         if (smaller && bigger)
//         {
//             if (abs(smaller->val - target) < abs(bigger->val - target))
//             {
//                 ans.push_back(smaller->val);
//                 smaller = getPrev(parent, smaller);
//             }
//             else
//             {
//                 ans.push_back(bigger->val);
//                 bigger = getNext(parent, bigger);
//             }
//         }
//         else if (smaller)
//         {
//             ans.push_back(smaller->val);
//             smaller = getPrev(parent, smaller);
//         }
//         else
//         {
//             ans.push_back(bigger->val);
//             bigger = getNext(parent, bigger);
//         }

//         i++;
//     }

//     return ans;
// }