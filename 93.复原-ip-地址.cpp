#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=93 lang=cpp
 *
 * [93] 复原 IP 地址
 */

// @lc code=start
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.size(); 
        vector<int> ip;
        vector<string> ips; 

        function<void(int)> dfs = [&](int idx)
        { 
            if (idx == n)
            {
                if (ip.size() == 4){
                    string ip_str = to_string(ip[0]); 

                    for (int i = 1; i < 4; i++)
                    {
                        ip_str += "." + to_string(ip[i]); 
                    }

                    ips.push_back(ip_str); 
                }

                return; 
            }
                
            
            for (int j = idx ; j < n; j++)
            {
                string sub = s.substr(idx, j - idx + 1); 
                
                // not a number
                for (auto c : sub){
                    if (c < '0' || c > '9') return; 
                }

                // leading zeros
                if (sub.size() > 1 && sub[0] == '0') return; 

                int num = stoi(sub); 

                if (num > 255) return; 

                ip.push_back(num); 
                dfs(j+1);
                ip.pop_back(); 
            };
        };

        dfs(0); 

        return ips; 
        
    }
};
// @lc code=end

