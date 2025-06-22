#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=535 lang=cpp
 *
 * [535] TinyURL 的加密与解密
 */

// @lc code=start
class Solution {
    private:
        unordered_map<int, string> dataBase;
        int id;
    
    public:
        Solution() {
            id = 0;
        }
    
        string encode(string longUrl) {
            id++;
            dataBase[id] = longUrl;
            return string("http://tinyurl.com/") + to_string(id);
        }
    
        string decode(string shortUrl) {
            int p = shortUrl.rfind('/') + 1;
            int key = stoi(shortUrl.substr(p, int(shortUrl.size()) - p));
            return dataBase[key];
        }
    };

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
// @lc code=end

