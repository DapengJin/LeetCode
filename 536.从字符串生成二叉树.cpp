#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=536 lang=cpp
 *
 * [536] 从字符串生成二叉树
 */

// @lc code=start
/**
 * 
 * test: 4(2(3)(1))(6(5))
 *   
 *        4
 *      /   \
 *     2     6
 *    / \    /
 *   3   1  5
 * 
 */

/**
 * 快速联想套路
 * 	1.	看见成对的括号 → 说明这是“嵌套”结构；
 * 	2.	嵌套 = 自相似 → 一定可以用“调用自己来处理更小的同样问题”（递归／分治）；
 * 	3.	要在一条字符串上来回扫，不想切子串 → 那就加个“全局”或“共享”的游标 index，按需递进。
 * 
 * 只要你在面试里一看到“类似 val(...) ( ... )”的格式，就默认这是一个可以“递归”出来的语法结构，
 * 接下来就想“把它当文法/语法树来写 parser”，最直接的手段就是递归函数 + 引用或全局的指针下标。
 * 
 * 这样，从“分治”到“递归 + index”就顺理成章了：
 * 
 * 分治告诉你“要把问题拆两个子树”；
 * 递归 + index告诉你“怎么在一条字符串里，把这两个子树读出来并拼回去”。
 */
class Solution
{
public:
    TreeNode *str2tree(string s)
    {
        int index = 0;
        return dfs(s, index);
    }

private:
    TreeNode *dfs(const string &s, int &index)
    {
        if (index >= s.size())
            return nullptr;

        // 解析节点值（整数）
        int val = parseInt(s, index);

        TreeNode *node = new TreeNode(val);

        // 解析左子树
        if (index < s.size() && s[index] == '(')
        {
            index++; // 跳过 '('
            node->left = dfs(s, index);
            index++; // 跳过 ')'
        }

        // 解析右子树
        if (index < s.size() && s[index] == '(')
        {
            index++; // 跳过 '('
            node->right = dfs(s, index);
            index++; // 跳过 ')'
        }

        return node;
    }

    int parseInt(const string &s, int &index)
    {
        int sign = 1, val = 0;
        if (s[index] == '-')
        {
            sign = -1;
            index++;
        }
        while (index < s.size() && isdigit(s[index]))
        {
            val = val * 10 + (s[index] - '0');
            index++;
        }
        return sign * val;
    }
};
// @lc code=end

class Solution
{
public:
    TreeNode *str2tree(string s)
    {
        int n = s.size();

        function<TreeNode *(string)> dfs = [&](string s) -> TreeNode *
        {
            if (s == "")
                return nullptr;

            int val = 0;
            int i = 0;
            int n = s.size();
            int sign = 1;

            while (i < n)
            {
                if (s[i] >= '0' && s[i] <= '9')
                {
                    val = val * 10 + s[i] - '0';
                    i++;
                }
                else if (s[i] == '-')
                {
                    sign = -1;
                    i++;
                }
                else
                    break;
            }

            if (i >= n)
                return new TreeNode(sign * val);

            int start = i;
            int cnt = 0;

            do
            {
                if (s[i] == '(')
                    cnt++;
                else if (s[i] == ')')
                    cnt--;

                i++;
            } while (cnt != 0);

            string sub1 =
                s.substr(min(n - 1, start + 1),
                         max(0, i - start - 2)); // remove the outer ()
            string sub2 =
                s.substr(min(n - 1, i + 1),
                         max(0, (int)s.size() - i - 2)); // remove the outer ()

            TreeNode *node = new TreeNode(sign * val);

            node->left = dfs(sub1);
            node->right = dfs(sub2);

            return node;
        };

        return dfs(s);
    }
};