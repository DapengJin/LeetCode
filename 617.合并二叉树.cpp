#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=617 lang=cpp
 *
 * [617] 合并二叉树
 */

// @lc code=start

struct TreeNode1 {
    pair<string,int> val;
    vector<TreeNode1 *>children;
    TreeNode1() {}
};

class Solution {
public:
    
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!(root1 && root2)) return root1 ? root1 : root2; 

        root1->val += root2->val; 

        root1->left = mergeTrees(root1->left, root2->left); 
        root1->right = mergeTrees(root1->right, root2->right); 

        return root1; 
    }

    // follow up: 如果是 N-ary tree，tree->val 是 key + val {A:3}。合并相同的 key 
    TreeNode1* mergeTrees1(TreeNode1* root1, TreeNode1* root2) {
        if (!(root1 && root2)) return root1 ? root1 : root2; 

        root1->val.second += root2->val.second; 

        // 一颗树的节点是 {A: 3}，子节点是[{F:3}, {B:1}, {R:6}]
        // 二颗树的节点是 {A: 8}，子节点是[{F:7}, {R:3}]
        unordered_map<string, TreeNode1*> dict1; 
        for (auto child: root1->children)
            dict1[child->val.first] = child; // {F: node, B: node, R: node}

        int n = root1->children.size(); 

        // 如果第一颗树有的节点 第二颗树 没有， 就不用管
        // 但是第二颗树都是要做处理的
        for (auto child2 : root2->children) 
        {
            if (dict1.contains(child2->val.first)) 
                // 不用 child = ... 因为 child 不会为 nullptr
                mergeTrees1(dict1[child2->val.first], child2); 
            else
            { 
                root1->children.push_back(child2);
            }
        }

        return root1; 
    }
};
// @lc code=end


