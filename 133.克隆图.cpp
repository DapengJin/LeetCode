#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=133 lang=cpp
 *
 * [133] 克隆图
 */
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


// @lc code=start
class Solution {
public:
    Node* cloneGraph(Node* node) {
        // old2new 用于记录：原节点指针 -> 克隆后新节点指针
        unordered_map<Node*, Node*> old2new; 

        // 返回 new_node
        function<Node *(Node *)> dfs = [&](Node* node) -> Node *
        { 
            // 如果该节点已被克隆过，直接返回其克隆对象
            if (old2new.contains(node)) return old2new[node]; 

            // 克隆当前节点（只复制 val，不复制 neighbors）
            Node* new_node = new Node(node->val); 
            // 添加映射
            old2new[node] = new_node; 

            // 递归克隆所有邻居，并加入到 clone 的 neighbors 列表
            for (auto neibor : node->neighbors)
                new_node->neighbors.push_back(dfs(neibor)); 

            return new_node; 
        };

        // 从给定的起始节点开始 DFS 克隆整张图
        return dfs(node); 
    }
};
// @lc code=end

