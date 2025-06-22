#include "pkgs.h"
/**
 * 这个题目是个经典的 T9 predictive text 问题的变体，核心目标是：
 *
 * 题意总结：
 *
 *  给定：
 *      •	一个 word list，如：["abc", "ace", "bat"]
 *      •	一个 数字串，如："223"
 *
 *  要找出所有能用九宫格数字 "223" 转换出的单词，并且出现在 word list 里。
 */
class TrieNode
{
public:
    bool is_word = false;
    unordered_map<char, TrieNode *> children;
};
class Solution
{
    TrieNode *root;
    unordered_map<char, string> digit_to_chars = {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, 
        {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, 
        {'8', "tuv"}, {'9', "wxyz"}};

public:
    Solution() : root(new TrieNode()) {}

    void build_trie(const vector<string> &wordList)
    {
        for (auto word : wordList)
        {
            auto cur = root;

            for (auto c : word)
            {
                if (!cur->children.contains(c))
                    cur->children[c] = new TrieNode();

                cur = cur->children[c];
            }

            cur->is_word = true;
        }
    }

    vector<string> t9Match(const vector<string> &wordList, const string &digits)
    {
        build_trie(wordList);

        int n = digits.size();
        vector<string> res;

        function<void(int, string, TrieNode *)> dfs = [&](int i, string path, TrieNode *node)
        {
            if (i == n)
            {
                if (node->is_word)
                    res.push_back(path);
                return;
            }

            char digit = digits[i];

            for (char c : digit_to_chars[digit])
            {
                if (!node->children.contains(c))
                    continue;

                dfs(i + 1, path + string(1, c), node->children[c]);
            }
        };

        dfs(0, "", root);

        return res;
    }
};

int main()
{
    Solution sol;
    vector<string> wordList = {"ace", "abc", "bat", "bad", "cad", "dog"};
    string digits = "223";

    vector<string> matches = sol.t9Match(wordList, digits);

    cout << "Words matching '" << digits << "':" << endl;
    for (const string &word : matches)
    {
        cout << word << endl;
    }

    return 0;
}