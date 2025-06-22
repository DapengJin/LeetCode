#include "pkgs.h"

class Solution
{
public:
    int perfectMenu(vector<int> &materials, vector<vector<int>> &cookbooks,
                    vector<vector<int>> &attribute, int limit)
    {
        int res = -1, n = cookbooks.size();

        /* 解2: 选第几个 */
        function<void(int, int, int)> dfs = [&](int i, int l, int s)
        {
            if (l >= limit)
                res = max(res, s);

            for (int j = i; j < n; j++)
            {

                bool cookable = true;

                for (int k = 0; k < 5; k++)
                {
                    if (materials[k] < cookbooks[j][k])
                    {
                        cookable = false;
                        break;
                    }
                }

                if (cookable == false)
                    continue;

                for (int k = 0; k < 5; k++)
                    materials[k] -= cookbooks[j][k];

                dfs(j + 1, l + attribute[j][1], s + attribute[j][0]);

                for (int k = 0; k < 5; k++)
                    materials[k] += cookbooks[j][k];
            }
        };

        /* 解1: 选/不选 */
        // function<void(int, int, int)> dfs = [&](int i, int l, int s)
        // {
        //     if (i == n)
        //     {
        //         if (l >= limit)
        //             res = max(res, s);
        //         return;
        //     }

        //     bool cookable = true;

        //     for (int j = 0; j < 5; j++)
        //     {
        //         if (materials[j] < cookbooks[i][j])
        //         {
        //             cookable = false;
        //             break;
        //         }
        //     }

        //     // 不选
        //     dfs(i + 1, l, s);

        //     // 有材料的情况下才能选
        //     if (cookable)
        //     {
        //         for (int j = 0; j < 5; j++)
        //             materials[j] -= cookbooks[i][j];

        //         dfs(i + 1, l + attribute[i][1], s + attribute[i][0]);

        //         for (int j = 0; j < 5; j++) // restore
        //             materials[j] += cookbooks[i][j];
        //     }
        // };

        dfs(0, 0, 0);

        return res;
    }
};

int main()
{
    Solution solution;

    // Test case input
    vector<int> materials = {3, 2, 4, 1, 2};
    vector<vector<int>> cookbooks = {
        {1, 1, 0, 1, 2},
        {2, 1, 4, 0, 0},
        {3, 2, 4, 1, 0}};
    vector<vector<int>> attribute = {
        {3, 2},
        {2, 4},
        {7, 6}};
    int limit = 5;

    // Call the function and print the result
    int result = solution.perfectMenu(materials, cookbooks, attribute, limit);
    cout << "Maximum attribute: " << result << endl;

    return 0;
}