#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=364 lang=cpp
 *
 * [364] 嵌套列表加权和 II
 *
 * 给你一个整数嵌套列表 nestedList ，每一个元素要么是一个整数，要么是一个列表
 * （这个列表中的每个元素也同样是整数或列表）。
 *
 * 整数的 深度 取决于它位于多少个列表内部。
 * 例如，嵌套列表 [1,[2,2],[[3],2],1] 的每个整数的值都等于它的 深度 。
 * 令 maxDepth 是任意整数的 最大深度 。
 *
 * 整数的 权重 为 maxDepth - (整数的深度) + 1 。
 *
 * 将 nestedList 列表中每个整数先乘权重再求和，返回该加权和。
 *
 * 示例 1：
 *     输入：nestedList = [[1,1],2,[1,1]]
 *          depth      =   2 2  1  2 2
 *          maxDepth   = 2
 *          weight     =   1 1  2  1 1
 *     输出：8
 *     解释：4 个 1 在深度为 1 的位置， 一个 2 在深度为 2 的位置。
 *     1*1 + 1*1 + 2*2 + 1*1 + 1*1 = 8
 *
 * 示例 2：
 *     输入：nestedList = [1,[4,[6]]]
 *          depth      =  1  2  3
 *          maxDepth   = 3
 *          weight     =  3  2  1
 *     输出：17
 *     解释：一个 1 在深度为 3 的位置， 一个 4 在深度为 2 的位置，一个 6 在深度为 1 的位置。
 *     1*3 + 4*2 + 6*1 = 17
 *
 * 提示：
 *     1 <= nestedList.length <= 50
 *     嵌套列表中整数的值在范围 [-100, 100]
 *     任意整数的最大 深度 小于等于 50
 *     没有空列表
 */
// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger
{
public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};
// @lc code=start
class Solution
{

public:
    /** 
     * weight_i = maxDepth - depth_i + 1
     * 
     * res = ∑(a_i * weight_i)
     *     = ∑(a_i * (maxDepth - depth_i + 1))
     *     = ∑(a_i * maxDepth) - ∑(a_i * depth_i) + ∑(a_i)
     *     = maxDepth * ∑(a_i) - ∑(a_i * depth_i) + ∑(a_i)
     *     = (maxDepth + 1) * ∑(a_i) - ∑(a_i * depth_i)
     *       (max_depth +1)   sum_x    sum_x_depth   
    */
    int depthSumInverse(vector<NestedInteger> &nestedList)
    {
        int sum_x = 0, sum_x_depth = 0, max_depth = 0;

        // dfs(int level)
        function<void(vector<NestedInteger> &, int)> dfs =
            [&](vector<NestedInteger> &nestedList, int level)
        {
            // traverse the vector
            for (auto x : nestedList)
            {
                // if the element is interger, compute something
                if (x.isInteger())
                {
                    sum_x += x.getInteger();
                    sum_x_depth += x.getInteger() * level;
                    max_depth = max(max_depth, level);
                    continue;
                }

                // if it is not an interger, call dfs to traverse it's
                // vector.
                dfs(x.getList(), level + 1);
            }
        };

        dfs(nestedList, 1);

        return (max_depth + 1) * sum_x - sum_x_depth;
    }
};
// @lc code=end
