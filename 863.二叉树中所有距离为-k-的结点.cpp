#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=863 lang=cpp
 *
 * [863] 二叉树中所有距离为 K 的结点
 */

// @lc code=start
class Solution
{
public:
    vector<int> distanceK(TreeNode *root, TreeNode *target, int K)
    {
        // 1. 建立 parent 指针映射
        unordered_map<TreeNode *, TreeNode *> parent;
        dfsBuildParent(root, nullptr, parent);

        // 2. 从 target 起 BFS 到距离 K
        vector<int> ans;
        unordered_set<TreeNode *> seen;
        queue<TreeNode *> q;

        q.push(target);
        seen.insert(target);
        int dist = 0;

        while (!q.empty())
        {
            int sz = q.size();
            // 如果到达第 K 层，队中所有节点就是答案
            if (dist == K)
            {
                while (sz--)
                {
                    ans.push_back(q.front()->val);
                    q.pop();
                }
                break;
            }
            // 否则继续扩展到下一层
            while (sz--)
            {
                TreeNode *u = q.front();
                q.pop();
                // 三个可能的邻居
                for (TreeNode *v : {u->left, u->right, parent[u]})
                {
                    if (v && !seen.count(v))
                    {
                        seen.insert(v);
                        q.push(v);
                    }
                }
            }
            dist++;
        }
        return ans;
    }

private:
    // DFS 构建 parent 映射
    void dfsBuildParent(TreeNode *node,
                        TreeNode *par,
                        unordered_map<TreeNode *, TreeNode *> &parent)
    {
        if (!node)
            return;
        parent[node] = par;
        dfsBuildParent(node->left, node, parent);
        dfsBuildParent(node->right, node, parent);
    }
};
// @lc code=end

/**
 * target = 2
 *
 *          3
 *        /   \
 *       5      1
 *      / \    / \
 *     6  '2' 0   8
 *        / \
 *       7   4
 *
 *   dfs 向上找，collect 向下找，把所有调用到 collect(node, …) 的节点数字都替换成 c
 *
 *          3
 *        /   \
 *       5     c
 *      / \   / \
 *     c   c 0   8
 *        / \
 *       c   c
 *
 */
class Solution
{
    vector<int> ans;
    int K;

public:
    vector<int> distanceK(TreeNode *root, TreeNode *target, int K)
    {
        this->K = K;
        dfs(root, target);
        return ans;
    }

private:
    // dfs 返回：node 到 target 的距离（若子树里没有 target，返回 -1）
    int dfs(TreeNode *node, TreeNode *target)
    {
        if (node == nullptr)
            return -1;

        if (node == target)
        {
            // 找到 target 之后，向下搜集距离为 K 的所有节点
            collect(node, 0);
            return 1;
        }

        // 在左子树寻找
        int ld = dfs(node->left, target);
        if (ld != -1)
        {
            // 左子树找到了 target，且其距离是 ld
            if (ld == K)
                ans.push_back(node->val);
            // 还要在右子树里找 距离为 K-(ld+1) 的节点
            collect(node->right, ld + 1);
            return ld + 1;
        }

        // 在右子树寻找
        int rd = dfs(node->right, target);
        if (rd != -1)
        {
            if (rd == K)
                ans.push_back(node->val);
            collect(node->left, rd + 1);
            return rd + 1;
        }
        return -1; // 本子树不含 target
    }

    // 从 node 向下搜集所有距离为 K 的节点
    void collect(TreeNode *node, int dist)
    {
        if (node == nullptr)
            return;

        if (dist == K)
            ans.push_back(node->val);
        else
        {
            collect(node->left, dist + 1);
            collect(node->right, dist + 1);
        }
    }
};