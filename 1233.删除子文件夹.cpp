#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1233 lang=cpp
 *
 * [1233] 删除子文件夹
 */

// @lc code=start
struct Trie{ 
    int ref; 
    unordered_map<string, Trie*> children; 

    Trie (): ref(-1) {}
}; 

class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // put all the strings that separated by / into the trie
        auto root = new Trie(); 

        auto split = [](const string& s) -> vector<string> {
            vector<string> ret;
            string cur;
            for (char ch: s) {
                if (ch == '/') {
                    ret.push_back(move(cur));
                    cur.clear();
                }
                else {
                    cur.push_back(ch);
                }
            }
            ret.push_back(move(cur));
            return ret;
        };

        // build trie
        for (int i = 0; i < folder.size(); i++)
        { 
            vector<string> path = split(folder[i]); 

            auto cur = root; 

            for (auto p : path) 
            { 
                if (!cur->children.contains(p))
                    cur->children[p] = new Trie(); 

                cur = cur->children[p]; 
            }

            cur->ref = i; 
        }

        vector<string> res; 

        // dfs to find the first parent folder
        function<void(Trie*)> dfs = [&](Trie * node){ 
            if (node->ref != -1){ 
                res.push_back(folder[node->ref]); 
                return; 
            }

            for (auto [s, n] : node->children){ 
                dfs(n); 
            }
        };

        dfs(root); 

        return res; 
    }
};
// @lc code=end

