#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=65 lang=cpp
 *
 * [65] 有效数字
 */

// @lc code=start
/**
 * 解1: 状态机
 * 解2: 模块化 unsigned int 和 int
 * 
 * Meta 简化版 没有 e：
 *      判断是不是 Number, 
 *          ✅ “11111”
 *          ✅ “1.08”
 *          ❌ “1ABC”
 *          ❌ “1.1.1.1”
 */
class Solution
{
public:
    enum State
    {
        STATE_INITIAL,
        STATE_INT_SIGN,
        STATE_INTEGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION,
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END
    };

    enum CharType
    {
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_ILLEGAL
    };

    CharType toCharType(char ch)
    {
        if (ch >= '0' && ch <= '9')
        {
            return CHAR_NUMBER;
        }
        else if (ch == 'e' || ch == 'E')
        {
            return CHAR_EXP;
        }
        else if (ch == '.')
        {
            return CHAR_POINT;
        }
        else if (ch == '+' || ch == '-')
        {
            return CHAR_SIGN;
        }
        else
        {
            return CHAR_ILLEGAL;
        }
    }

    bool isNumber(string s)
    {

        unordered_map<State, unordered_map<CharType, State>> transfer
        {
            {
                STATE_INITIAL, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                    {CHAR_SIGN, STATE_INT_SIGN}
                }
            }, {
                STATE_INT_SIGN, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT}
                }
            }, {
                STATE_INTEGER, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_POINT, STATE_POINT}
                }
            }, {
                STATE_POINT, {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP}
                }
            }, {
                STATE_POINT_WITHOUT_INT, {
                    {CHAR_NUMBER, STATE_FRACTION}
                }
            }, {
                STATE_FRACTION,
                {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP}
                }
            }, {
                STATE_EXP,
                {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SIGN, STATE_EXP_SIGN}
                }
            }, {
                STATE_EXP_SIGN, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER}
                }
            }, {
                STATE_EXP_NUMBER, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER}
                }
            }
        };

        State st = STATE_INITIAL;

        for (auto c : s)
        {
            auto ctp = toCharType(c);

            if (!transfer[st].contains(ctp))
                return false;
            else
            {
                st = transfer[st][ctp];
            }
        }

        return st == STATE_INTEGER ||
               st == STATE_POINT || 
               st == STATE_FRACTION || 
               st == STATE_EXP_NUMBER || 
               st == STATE_END;
    }
};
// @lc code=end

class Solution1
{
public:
    bool isUInt(string &s, int &i)
    { // 判断无符号整数
        int pre_i = i;

        while (i < s.size() && '0' <= s[i] && s[i] <= '9')
            i++;

        return pre_i != i;
    }

    bool isInt(string &s, int &i)
    { // 判断是不是整数 (可能带正负号)
        if (i < s.size() && s[i] == '+' || s[i] == '-')
            i++; // -.5 也可以处理

        return isUInt(s, i);
    }

    // 有效数字的结构是 (int)(.)(uint)(e && int)
    bool isNumber(string s)
    {
        int i = 0;
        bool res = false; // 假设这是一个无效数字

        res = isInt(s, i);

        // met a decimal point
        if (i < s.size() && s[i] == '.')
        {
            i++;
            // !!! Since i changed, out-of-range should be checked in isUInt
            // !!! res || isUInt(s, i) is wrong.
            //     if res == true, isUInt(s, i) won't get executed !!!
            res = isUInt(s, i) || res; // 如果有小数点，只有前后都没有数字才不对
        }

        if (i < s.size() && tolower(s[i]) == 'e')
        {
            i++;
            // !!! Since i changed, out-of-range should be checked in isInt
            // !!! && e must have integer on both side
            res = res && isInt(s, i); // 如果出现指数e，则e的前后都必须要有整数
        }

        return res && i == s.size();
    }
};


class Solution2 {
    bool isUInt(string &s, int &i) 
    { 
        int i0 = i; 

        while (isdigit(s[i]))
            i++;

        return i0 != i; 
    }

    bool isInt(string &s, int &i)
    { 
        if (s[i] == '+' || s[i] == '-')
            i++; // 处理 +.5 的情况

        return isUInt(s, i); 
    }
public:
    bool isNumber(string s) {
        int i = 0; 
        bool res = isInt(s,i);

        if (s[i] == '.')
        {
            i++; 
            res = isUInt(s,i) || res; // isUInt(s,i) 要先判断
        }

        return res && 
               i == s.size(); // 已经处理完所有字符
    }
};