#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=114 lang=cpp
 *
 * [114] 二叉树展开为链表
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
class Solution1
{
    TreeNode *head; // 用于记录已经展开成链表的部分的头节点
public:
    // 从尾巴开始往前遍历
    void flatten(TreeNode *root)
    {
        if (root == nullptr)
            return;

        flatten(root->right);
        flatten(root->left);

        root->left = nullptr;
        root->right = head; // 头插法，相当于链表的 root->next = head
        head = root;        // 现在链表头节点是 root
    }
};

class Solution2
{
    // 返回当前子树展开后链表的尾节点
    TreeNode *dfs(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *left_tail = dfs(root->left);
        TreeNode *right_tail = dfs(root->right);

        if (left_tail)
        {
            left_tail->right = root->right; // 左子树链表 -> 右子树链表
            root->right = root->left;       // 当前节点 -> 左右子树合并后的链表
            root->left = nullptr;
        }

        return right_tail  ? right_tail // 右子树存在，右子树的尾巴就是整棵树的尾巴；
               : left_tail ? left_tail  // 否则，如果左子树存在，那就是左尾；
                           : root;      // 当前 root 自己就是叶子节点，是尾巴
    }

public:
    void flatten(TreeNode *root)
    {
        dfs(root);
    }
};

class Solution
{
public:
    void flatten(TreeNode *root)
    {
        TreeNode *cur = root;

        // 遍历整棵树，每次处理当前节点 cur
        while (cur != nullptr)
        {

            // 如果当前节点有左子树，就要把它“搬”到右边
            if (cur->left != nullptr)
            {
                // 先找到左子树的最右边节点（即前序遍历中左子树的尾节点）
                auto nxt = cur->left;
                auto predecessor = nxt;


                /**
                 *           1  <- cur    |         1
                 *          / \           |        /
                 * nxt ->  2   6          |       2  
                 *        / \   \         |      / \ 
                 *       3   4   7        |     3   4  
                 *            \           |          \
                 *             5  <- pre  |           5
                 *                        |            \
                 *                        |             6
                 *                        |              \
                 *                        |               7 
                 */
                while (predecessor->right != nullptr)
                    predecessor = predecessor->right;

                // 将右子树接到左子树的最右节点后面
                predecessor->right = cur->right;

                /**
                 *          1  <- cur
                 *           \
                 *            2  <- nxt
                 *           / \ 
                 *          3   4  
                 *               \
                 *                5
                 *                 \
                 *                  6
                 *                   \
                 *                    7 
                 * 
                 */
                // 将左子树移到右边
                cur->left = nullptr;
                cur->right = nxt;
            }

            // 移动到右子树，继续处理下一个节点
            cur = cur->right;
        }
    }
};
// @lc code=end
