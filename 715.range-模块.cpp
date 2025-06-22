#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=715 lang=cpp
 *
 * [715] Range 模块
 */

// @lc code=start
class RangeModule
{
private:
    static const int N = 1e9; // 区间范围 [0, 1e9)，题目要求的最大值
    struct Node
    {
        Node *left = nullptr;  // 左子区间
        Node *right = nullptr; // 右子区间
        bool covered = false;  // 当前区间是否被完全 add 覆盖
        int lazy = -1;         // 懒惰标记：-1表示没有标记，0表示清除，1表示添加
    };

    Node *root; // 根节点，代表整个 [0, 1e9) 区间

    // 懒惰下推，将父节点的 lazy 更新传递给子节点
    // 每个递归下去前都 pushDown，把懒惰标记传下去
    void pushDown(Node *node)
    {
        // 如果左右子节点不存在就动态创建
        if (!node->left)
            node->left = new Node();
        if (!node->right)
            node->right = new Node();

        // 如果当前节点有懒惰标记，则下推给子节点
        if (node->lazy != -1)
        {
            node->left->covered = node->right->covered = node->lazy; // 更新子节点是否被覆盖
            node->left->lazy = node->right->lazy = node->lazy;       // 传递 lazy 标记
            node->lazy = -1;                                         // 当前节点标记已下推，清除
        }
    }

    // 更新区间 [start, end) 为覆盖或取消覆盖（val = true 表示 add，false 表示 remove）
    void update(Node *node, int l, int r, int start, int end, bool val)
    {
        // 如果当前区间 [l, r) 和目标区间 [start, end) 没有交集，直接返回
        if (start >= r || end <= l)
            return;

        // 当前区间被完全包含在目标更新区间中，直接打标记
        if (start <= l && r <= end)
        {
            node->covered = val;
            node->lazy = val;
            return;
        }

        // 否则，进行懒惰下推 + 向子区间递归更新
        pushDown(node); // 每个递归下去前都 pushDown，把懒惰标记传下去
        int mid = l + (r - l) / 2;
        update(node->left, l, mid, start, end, val);
        update(node->right, mid, r, start, end, val);

        // 当前节点是否被覆盖，取决于左右子节点是否都被覆盖
        node->covered = node->left->covered && node->right->covered;
    }

    // 查询区间 [start, end) 是否全部被 add 过
    bool query(Node *node, int l, int r, int start, int end)
    {
        // 不相交，直接返回 true（因为不影响结果）
        if (start >= r || end <= l)
            return true;

        // 当前节点完全被包含在查询区间内，返回标记
        if (start <= l && r <= end)
            return node->covered;

        // 没有子节点，说明没有被标记，返回当前节点状态
        if (!node->left)
            return node->covered;

        // 否则递归查询左右子树
        pushDown(node); // 每个递归下去前都 pushDown，把懒惰标记传下去
        int mid = l + (r - l) / 2;
        return query(node->left, l, mid, start, end) &&
               query(node->right, mid, r, start, end);
    }

public:
    // 构造函数，初始化根节点
    RangeModule()
    {
        root = new Node();
    }

    // 添加区间 [left, right)
    void addRange(int left, int right)
    {
        update(root, 0, N, left, right, true);
    }

    // 移除区间 [left, right)
    void removeRange(int left, int right)
    {
        update(root, 0, N, left, right, false);
    }

    // 查询区间 [left, right) 是否被完全覆盖
    bool queryRange(int left, int right)
    {
        return query(root, 0, N, left, right);
    }
};
// @lc code=end
