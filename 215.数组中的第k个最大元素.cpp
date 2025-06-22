#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */

// @lc code=start
class PQ
{
private:
    vector<int> q{INT_MIN};

    void siftDown(int i)
    {
        int smallest = i, left = 2 * i, right = left + 1;

        if (left < q.size() && q[left] < q[smallest])
            smallest = left;

        if (right < q.size() && q[right] < q[smallest])
            smallest = right;

        if (i != smallest)
        {
            swap(q[i], q[smallest]);
            siftDown(smallest);
        }
    }

    void bubbleUp(int i)
    {
        if (i <= 1)
            return; // root 节点

        int parent = i / 2;

        if (q[parent] > q[i])
        { // 如果当前节点比父节点大，交换并递归向上调整
            swap(q[parent], q[i]);
            bubbleUp(parent);
        }
    }

public:
    PQ(vector<int> nums = {})
    {
        q.insert(q.end(), nums.begin(), nums.end());

        for (int i = (q.size() -1)/2 ; i > 1 ; i-- )
        {
            siftDown(i); 
        }
    }

    int size()
    {
        return q.size() - 1;
    }

    void pop()
    {
        swap(q[1], q[q.size() - 1]);
        q.pop_back();
        siftDown(1);
    }

    void push(int x)
    {
        q.push_back(x);
        bubbleUp(q.size() - 1);
    }

    int top()
    {
        return q[1];
    }
};

class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        // priority_queue<int, vector<int>, greater<int>> min_heap;
        PQ min_heap;

        for (auto x : nums)
        {
            min_heap.push(x);

            if (min_heap.size() > k)
                min_heap.pop();
        }

        return min_heap.top();
    }

    /**
     * find the k-th smallest element
     * 
     *  Hoare partition
     *  外起步，先动步；  “外围启动，先动再判断”
     *  左跳小，右跳大；  “左边跳过小的，右边跳过大的”
     *  交换条件 i < j；
     *  终止返回是 j 点。
     * 
     *  */ 
    int quickselect(vector<int> &nums, int l, int r, int k)
    {
        // l == r == k
        if (l == r)
            return nums[k];

        // 使用 Hoare 分区，选择第一个数为 pivot
        int pivot = nums[l], i = l - 1, j = r + 1;

        while (i < j)
        {
            do i++; while (nums[i] < pivot);// 左跳：跳过所有小于 pivot 的数
            do j--; while (nums[j] > pivot);// 右跳：跳过所有大于 pivot 的数
            
            if (i < j) // i < j 才交换，确保不越界
                swap(nums[i], nums[j]);
        }

        // 此时 j 是最后一个 <= pivot 的位置，划分为 [l..j] 和 [j+1..r]
        return k <= j ? // j 是第一个 nums[j] <= pivot 的点
                        // i 是第一个 nums[i] >= pivot 的点
                        // 如果 把 j 替换成 i-1，i-1 可能越界了（infinite loop）
                quickselect(nums, l, j, k) :    // k 在左半边
                quickselect(nums, j + 1, r, k); // k 在右半边
    }

    // 寻找数组中第 k 大的元素 => 等价于第 (n-k+1) 小
    int findKthLargest1(vector<int> &nums, int k)
    {
        int n = nums.size();
        return quickselect(nums, 0, n - 1, n - k); // n-k 是因为 0-indexed
    }
};
// @lc code=end

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4}; 
    int k = 2; // 找第 2 大的数
    Solution s; 
    int result = s.findKthLargest(nums, k);
    
    cout << "The " << k << "th smallest element is: " << result << endl;

    return 0;
}