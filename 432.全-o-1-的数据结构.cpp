#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=432 lang=cpp
 *
 * [432] 全 O(1) 的数据结构
 */
// https://leetcode.cn/problems/all-oone-data-structure/solutions/1341837/shu-ju-jie-gou-set-by-constant-r-ubz1/
// @lc code=start

/** Double LinkedList + unordered_map */
/**
 * @brief  维护字符串的频率，并能快速获取最小和最大频率的字符串。
 *
 * 主要使用：
 * - **双向链表 (`list`)**：按频率存储 `unordered_set<string>`，其中 `unordered_set` 记录所有相同频率的字符串。
 * - **哈希表 (`unordered_map`)**：快速找到字符串在链表中的位置，支持 O(1) 访问和更新。
 */

class AllOne
{
    // 双向链表，每个节点存储一个 (字符串集合, 频率)
    list<pair<unordered_set<string>, int>> lst;
    // 哈希表，存储 key 对应的链表节点的迭代器
    unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> nodes;

public:
    AllOne() {}

    void inc(string key)
    {
        if (nodes.contains(key)) // 如果 key 已存在
        {
            auto cur = nodes[key], nxt = next(cur); // 找到 key 当前的迭代器，并尝试获取下一个节点

            // 从当前频率层移除 key
            cur->first.erase(key);

            // 已有频率为 当前频率+1 的层
            if (nxt != lst.end() && nxt->second == cur->second + 1)
            {
                // 直接将 key 移动到下一个频率层
                nxt->first.emplace(key);
                // 更新 iterator
                nodes[key] = nxt;
            }
            else // 新建一个频率为 当前频率+1 的层
            {
                // 创建一个新节点 (key 频率 +1) 并插入链表
                unordered_set<string> s({key});
                // 更新 iterator
                nodes[key] = lst.emplace(nxt, s, cur->second + 1);
            }

            // 如果当前层变空，移除该层 !!! 需要在结束的时候做
            if (cur->first.empty())
            {
                lst.erase(cur);
            }
        }
        else // key 不存在
        {
            // 已有 频率 为 1 的层
            if (lst.size() && lst.begin()->second == 1)
            {
                lst.begin()->first.emplace(key);
            }
            else // 新建一个频率为 1 的节点
            {
                unordered_set<string> s({key});
                lst.emplace_front(s, 1);
            }

            // 更新 key 的位置
            nodes[key] = lst.begin();
        }
    }

    void dec(string key)
    {
        auto cur = nodes[key];

        // 从当前层移除 key
        cur->first.erase(key);

        if (cur->second == 1)
            // key 仅出现一次，将其移出 nodes
            nodes.erase(key);
        else
        {
            auto pre = prev(cur);

            // pre 不为空，且为 当前频率-1 的层
            if (cur != lst.begin() && pre->second == cur->second - 1)
            {
                pre->first.emplace(key);
                nodes[key] = pre;
            }
            else// 新建一个频率为 当前频率-1 的层
            {
                unordered_set<string> s({key});
                nodes[key] = lst.emplace(cur, s, cur->second - 1);
            }
        }

        // 如果当前层变空，移除该层 !!! 需要在结束的时候做
        if (cur->first.empty())
        {
            lst.erase(cur);
        }
    }

    string getMaxKey()
    {
        return lst.empty() ? "" : *lst.rbegin()->first.begin();
    }

    string getMinKey()
    {
        return lst.empty() ? "" : *lst.begin()->first.begin();
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
// @lc code=end

/** 两个 map */
class AllOne2
{
public:
    // set<pair<int, string>> sort;
    map<int, unordered_set<string>> sort;
    unordered_map<string, int> counter;

    AllOne2()
    {
    }

    void inc(string key)
    {
        int count = counter[key]++;

        if (count)
        {
            // 从原来的计数分组中移除 key，并在该组为空时删除该分组
            sort[count].erase(key);
            if (sort[count].empty())
                sort.erase(count);
        }

        sort[count + 1].insert(key);
    }

    void dec(string key)
    {
        int count = counter[key]--;

        // 从原来的计数分组中移除 key，并在该组为空时删除该分组
        sort[count].erase(key);
        if (sort[count].empty())
            sort.erase(count);

        if (count == 1)
            counter.erase(key);
        else
            sort[count - 1].insert(key);
    }

    string getMaxKey()
    {
        if (sort.empty())
            return "";

        return *(sort.rbegin()->second.begin());
    }

    string getMinKey()
    {
        if (sort.empty())
            return "";

        return *(sort.begin()->second.begin());
    }
};
