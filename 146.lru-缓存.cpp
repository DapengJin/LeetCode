#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */

// @lc code=start
class Node
{
public:
    int key;
    int val;
    Node *pre;
    Node *nxt;

    Node(int k = 0, int v = 0) : key(k), val(v)
    {
    }
};

class LRUCache
{
private: 
    int capacity; 
    Node * dummy;
    unordered_map<int, Node*> key_to_node; 

    // 删除一个节点（抽出一本书）
    void remove(Node *node)
    { 
        node->pre->nxt = node->nxt; 
        node->nxt->pre = node->pre; 
    }

    // 在链表头添加一个节点（把一本书放在最上面）
    void push_front(Node* node)
    {
        node->pre = dummy;
        node->nxt = dummy->nxt; 
        dummy->nxt->pre = node; 
        dummy->nxt = node; 
    }

    // 获取 key 对应的节点，同时把该节点移到链表头部
    Node* get_node(int key)
    {
        if (!key_to_node.contains(key)) return nullptr; 

        Node *node = key_to_node[key]; 
        remove(node); 
        push_front(node); 

        return node; 
    }

public:
    LRUCache(int capacity) : capacity(capacity), dummy(new Node())
    {
        dummy->pre = dummy; 
        dummy->nxt = dummy; 
    }

    int get(int key)
    {
        Node* node = get_node(key);

        return node? node->val : -1; 
    }

    void put(int key, int value)
    {
        Node* node = get_node(key);

        if (node) { // 有这本书
            node->val = value; // 更新 value
            return;
        }

        node = new Node(key, value); 

        if (key_to_node.size() == capacity) // 到达容量 先移除 再添加
        { 
            Node *back = dummy->pre; 
            key_to_node.erase(back->key);
            remove(back); 
            delete back; 
        }

        push_front(node); // 添加
        key_to_node[key] = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end


class LRUCache1 {
    int capacity;
    using ListIt = list<pair<int, int>>::iterator;
    unordered_map<int, list<pair<int, int>>::iterator> mp; // {key : iter}
    list<pair<int, int>> lst;                              // [key, val]
public:
    LRUCache1(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (!mp.contains(key))
            return -1;

        auto iter = mp[key];
        int res = iter->second;

        move_front(iter);

        return res;
    }

    void put(int key, int value) {
        if (mp.contains(key)) {
            auto iter = mp[key];
            iter->second = value;
            move_front(iter);
        } else {
            // check capacity
            if (lst.size() == capacity) {
                auto [k, v] = lst.back();
                mp.erase(k);
                lst.pop_back();
            }

            lst.push_front({key, value});
            mp[key] = lst.begin();
        }
    }

    // insert to front ｜ delete iter ｜ update map
    void move_front(list<pair<int, int>>::iterator iter) {
        // auto [k, v] = *iter; 

        // lst.erase(iter); 
        // lst.push_front({k,v}); 
        // mp[k] = lst.begin(); 
        lst.splice(lst.begin(), lst, iter); // 直接将 iter 移到最前面
        // lst.splice(lst.begin(), lst, lst.begin(),lst.end()); 插入 range 的做法
    }
};
