#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 */

// @lc code=start
/* Bi-direction BFS */
class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> s1, s2, all(wordList.begin(), wordList.end());
        int len = wordList.size(), step = 1;

        if (!all.contains(endWord)) // endWord 也要连边的，要确保 endWord 在 wordList 里
            return 0;

        s1.emplace(beginWord); // 从 beginWord 起，离 beginWord 当前最远的点
        s2.emplace(endWord);

        while (!s1.empty() && !s2.empty())
        {
            step++;

            if (s1.size() > s2.size()) // 永远 explore 外层节点最少的边
                swap(s1, s2);

            for (const string &it : s1)
                all.erase(it); // 把已经找到最短路径的节点删了

            for (const string &it : s2)
                all.erase(it); // 把已经找到最短路径的节点删了

            unordered_set<string> s; // s1 的下一层

            for (string it : s1)
            {
                for (int i = 0; i < it.size(); i++)
                {
                    char temp = it[i];

                    for (int j = 'a'; j <= 'z'; j++)
                    {
                        it[i] = j;

                        // **终止条件**：如果新生成的单词已在 `s2` 中，说明两端 BFS 连接成功
                        if (s2.contains(it))
                            return step;

                        // 若单词不在 `all` 中，说明它已访问过或不是合法单词
                        if (!all.contains(it))
                            continue;

                        s.emplace(it); // s1 的下一层
                    }

                    it[i] = temp; // 复原原始单词，准备修改下一个字符
                }
            }

            s1 = s;
        }

        return 0;
    }
};
// @lc code=end

/* 反图 BFS */
class Solution1
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        // 使用 unordered_set 存储 wordList，方便快速查找
        unordered_set<string> words(wordList.begin(), wordList.end());
        words.insert(beginWord); // 确保 beginWord 也包含在 words 中

        // **构建反向图（back graph）**

        // cur_level / next_level 用一个 list 当 queue 就行
        vector<string> cur_level;                 // 当前层的单词
        vector<string> nxt_level;                 // 下一层的单词
        unordered_map<string, vector<string>> aj; // 记录从 beginWord <-- endWord 的反向图 （用不到）
        int level = 1;                            // 记录转换步数

        cur_level.push_back(beginWord); // BFS 从 beginWord 开始

        while (!cur_level.empty())
        {
            // **删除当前层的单词，避免重复访问**
            for (auto node : cur_level)
                words.erase(node);

            level++; // 进入下一层

            for (auto node : cur_level) // 遍历当前层的所有单词
            {
                auto child = node; // 复制当前单词

                for (int i = 0; i < node.size(); i++) // 逐个修改单词中的字符
                {
                    char tmp = child[i];

                    // **尝试将单词的每个字符替换为 'a' 到 'z'**
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        child[i] = ch;

                        // **如果修改后的单词在 wordList 中**
                        if (words.contains(child))
                        {
                            aj[child].push_back(node);  // 反向图连边
                            nxt_level.push_back(child); // 加入下一层队列

                            // **如果找到 endWord，返回当前层数**
                            if (child == endWord)
                                return level;
                        }
                    }

                    child[i] = tmp; // 复原单词，继续修改下一个字符
                }
            }

            cur_level = nxt_level; // 更新当前层
            nxt_level.clear();     // 清空下一层队列，准备下一次迭代
        }

        return 0; // 无法转换到 endWord
    }
};