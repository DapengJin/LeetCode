#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=249 lang=cpp
 *
 * [249] 移位字符串分组
 *
 * 对字符串进行 “移位” 的操作：
 *
 * 右移：将字符串中每个字母都变为其在字母表中 后续 的字母，其中用 'a' 替换 'z'。比如，"abc" 能够右移为 "bcd"，"xyz" 能够右移为 "yza"。
 * 左移：将字符串中每个字母都变为其在字母表中 之前 的字母，其中用 'z' 替换 'a'。比如，"bcd" 能够左移为 "abc"，"yza" 能够左移为 "xyz"。
 * 我们可以不断地向两个方向移动字符串，形成 无限的移位序列。
 *
 * 例如，移动 "abc" 来形成序列：... <-> "abc" <-> "bcd" <-> ... <-> "xyz" <-> "yza" <-> ... <-> "zab" <-> "abc" <-> ...
 * 给定一个字符串数组 strings，将属于相同移位序列的所有 strings[i] 进行分组。你可以以 任意顺序 返回答案。
 *
 *
 *
 * 示例 1：
 *
 *      输入：strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
 *
 *      输出：[["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
 *
 *
 *
 * 示例 2：
 *
 *      输入：strings = ["a"]
 *
 *      输出：[["a"]]
 *
 *
 *
 * 提示：
 *
 *      1 <= strings.length <= 200
 *      1 <= strings[i].length <= 50
 *      strings[i] 只包含小写英文字母。
 *
 *
 */

// @lc code=start
class Solution
{
public:
    vector<vector<string>> groupStrings(vector<string> &strings)
    {
        // 用于存放“签名”到字符串列表的映射
        unordered_map<string, vector<string>> mp;

        // 遍历每个输入字符串
        for (string &s : strings)
        {
            string key; // 本字符串对应的差分签名
            int n = s.size();

            // 计算相邻字符的环绕差值
            for (int i = 1; i < n; ++i)
            {
                // 'b' - 'a' = 1
                // 'a' - 'z' = 1
                char diff = (s[i] - s[i - 1] + 26) % 26;
                // 将差值映射到 'a'..'z' 之间的字符，构成签名
                key.push_back(diff);
            }

            // 长度为 1 的字符串，key 保持空 (所有单字符都分到同一组)

            // 将原字符串加入对应签名组
            mp[key].push_back(s);
        }

        // 将 map 中的每一组结果收集到最终返回的二维数组
        vector<vector<string>> res;

        for (auto &[_, group] : mp)
        {
            res.push_back(move(group));
        }
        return res;
    }
};
// @lc code=end
