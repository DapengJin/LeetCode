#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=314 lang=cpp
 *
 * [314] 二叉树的垂直遍历


给你一个二叉树的根结点，返回其结点按 垂直方向（从上到下，逐列）遍历的结果。

如果两个结点在同一行和列，那么顺序则为 从左到右。

 

示例 1：
    输入：root = [3,9,20,null,null,15,7]
    输出：[[9],[3,15],[20],[7]]

示例 2：
    输入：root = [3,9,8,4,0,1,7]
    输出：[[4],[9],[3,0,1],[8],[7]]

示例 3：
               1
             /    \ 
            2      3
           / \    / \
          4  (10,9)  11
           \    
            5   
             \  
               6
    输入：root = [1,2,3,4,10,9,11,null,5,null,null,null,null,null,null,null,6]
    输出：[[4],[2,5],[1,10,9,6],[3],[11]]
 

提示：

    树中结点的数目在范围 [0, 100] 内
    -100 <= Node.val <= 100


 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        map<int, vector<int>> m;
        vector<vector<int>>res; 

        if (root == nullptr) return {}; 
        
        // 只能用 BFS，因为 DFS 有可能 先访问更深的节点
        queue<pair<int,TreeNode*>> q; 

        q.push({0, root}); 

        while (q.size())
        { 
            int n = q.size(); 

            for (int i = 0; i < n ; i++)
            { 
                auto [pos, node] = q.front(); 
                
                q.pop(); 
                
                m[pos].push_back(node->val); 

                if (node-> left) q.push({pos - 1, node->left}); 
                if (node-> right) q.push({pos + 1, node->right}); 
            }
        }

        for (auto [_, vals] : m)
            res.push_back(vals); 

        return res; 
    }
};
// @lc code=end

