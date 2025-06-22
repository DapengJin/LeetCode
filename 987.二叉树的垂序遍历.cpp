#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=987 lang=cpp
 *
 * [987] 二叉树的垂序遍历
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> verticalTraversal(TreeNode *root)
    {
        vector<tuple<int, int, int>> nodes; // {col, row, val}

        // DFS 收集结点坐标
        function<void(TreeNode *, int, int)> dfs = [&](TreeNode *p, int r, int c)
        {
            if (p == nullptr) return;

            nodes.emplace_back(c, r, p->val);
            dfs(p->left, r + 1, c - 1);  // 左子树 col-1
            dfs(p->right, r + 1, c + 1); // 右子树 col+1
        };
        
        dfs(root, 0, 0);

        // ① 按列、②行、③值 三键排序
        sort(nodes.begin(), nodes.end(),
             [](auto &a, auto &b) { // 其实不用，就是从小到大
                 if (get<0>(a) != get<0>(b)) return get<0>(a) < get<0>(b);
                 if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b);
                 return get<2>(a) < get<2>(b);
             });

        // 根据 col 分组输出
        vector<vector<int>> res;
        int prevCol = INT_MIN;
        for (auto [c, r, v] : nodes)
        {
            if (c != prevCol) // 开启新列
            { 
                res.emplace_back();
                prevCol = c;
            }

            res.back().push_back(v);
        }

        return res;
    }
};
// @lc code=end
class Solution
{
    map<int, vector<pair<int, int>>> groups;

    void dfs(TreeNode *node, int row, int col)
    {
        if (node == nullptr)
            return;

        // col 相同的分到同一组
        groups[col].emplace_back(row, node->val);

        dfs(node->left, row + 1, col - 1);
        dfs(node->right, row + 1, col + 1);
    }

public:
    vector<vector<int>> verticalTraversal(TreeNode *root)
    {
        dfs(root, 0, 0);
        vector<vector<int>> res;

        for (auto &[_, g] : groups) // (row, val)
        {
            ranges::sort(g);
            vector<int> vals;

            // 将排好序的 val 提取到单独的数组中
            for (auto &[_, val] : g)
                vals.push_back(val);

            res.push_back(vals);
        }

        return res;
    }
};