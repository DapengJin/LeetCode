#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=380 lang=cpp
 *
 * [380] O(1) 时间插入、删除和获取随机元素
 */

// @lc code=start
class RandomizedSet
{
public:
    /**
     * unordered_map + vector
     *      Use a vector to store elements for O(1) random access.
     *      Use an unordered_map to map values to their indices for O(1) removal.
     *          remove 的时候，把最后一个元素和要删除的元素交换，然后删除最后一个元素
     */
    vector<int> elem;
    unordered_map<int, int> idx; // {value, index}

    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        if (!idx.contains(val))
        {
            idx[val] = elem.size();
            elem.push_back(val);
            return true;
        }

        return false;
    }

    bool remove(int val)
    {
        if (idx.contains(val))
        {
            int i = idx[val];

            // if (i != elem.size() - 1)
            // {
            //     swap(elem[i], elem[elem.size() - 1]);
            //     idx[elem[i]] = i;
            // }
            swap(elem[i], elem.back());

            // update index for the swapped value
            idx[elem[i]] = i;

            // remove deleted value 
            // (the swap might have no impact, val 可能本来就是最后一个)
            elem.pop_back();
            idx.erase(val);

            return true;
        }

        return false;
    }

    int getRandom()
    {
        int i = rand() % elem.size();

        return elem[i];
    }
};
// @lc code=end

// Follow up 如果允许 duplicates
class RandomizedSet1
{
public:
    vector<int> elem;                           // [val1, val2, ...]
    unordered_map<int, unordered_set<int>> idx; // {val: {indices}}

    RandomizedSet1()
    {
    }

    bool insert(int val)
    {
        if (!idx.contains(val))
        {
            idx[val].insert(elem.size());
            elem.push_back(val);
            return true;
        }

        return false;
    }

    bool remove(int val)
    {
        if (idx.contains(val))
        {
            int i = *idx[val].begin();
            int e = elem.size() - 1;

            if (i != e)
            {
                swap(elem[i], elem[e]);
                idx[elem[i]].erase(e);
                idx[elem[i]].insert(i);
            }

            // !!! remove at last
            elem.pop_back();
            idx[val].erase(i);

            if (idx[val].empty())
                idx.erase(val);

            return true;
        }

        return false;
    }

    int getRandom()
    {
        int i = rand() % elem.size();

        return elem[i];
    }
};