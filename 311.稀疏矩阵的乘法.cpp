#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=311 lang=cpp
 *
 * [311] 稀疏矩阵的乘法
 */

// @lc code=start
class Solution
{
    using VEC = vector<pair<int, int>>;
    int dot_prod(VEC v1, VEC v2)
    {
        int n1 = v1.size(), n2 = v2.size();
        int i1 = 0, i2 = 0;
        int res = 0;

        while (i1 < n1 && i2 < n2)
        {
            auto [x1, y1] = v1[i1];
            auto [x2, y2] = v2[i2];

            if (x1 > x2)
                i2++;
            else if (x1 < x2)
                i1++;
            else
            {
                res += y1 * y2;
                i1++;
                i2++;
            }
        }

        return res;
    }

public:
    vector<vector<int>> multiply(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
    {
        int m = mat1.size(), k = mat1[0].size(), n = mat2[0].size();

        vector<VEC> v1s, v2s;

        for (int i = 0; i < m; i++)
        {
            VEC v;
            for (int j = 0; j < k; j++)
            {
                if (mat1[i][j] == 0)
                    continue;

                v.push_back({j, mat1[i][j]});
            }
            v1s.push_back(v);
        }

        for (int i = 0; i < n; i++)
        {
            VEC v;
            for (int j = 0; j < k; j++)
            {
                if (mat2[j][i] == 0)
                    continue;

                v.push_back({j, mat2[j][i]});
            }
            v2s.push_back(v);
        }

        vector<vector<int>> res(m, vector(n, 0));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res[i][j] = dot_prod(v1s[i], v2s[j]);

        return res;
    }
};
// @lc code=end

/* 普通矩阵乘法 */
class Solution1
{
public:
    vector<vector<int>> multiply(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
    {
        int m = mat1.size(), mn = mat1[0].size(), n = mat2[0].size();
        vector res(m, vector(n, 0));

        for (int i = 0; i < m; i++)
            for (int ij = 0; ij < mn; ij++)
                for (int j = 0; j < n; j++)
                    res[i][j] += mat1[i][ij] * mat2[ij][j];

        return res;
    }
};