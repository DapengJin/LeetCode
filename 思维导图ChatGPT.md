# Leetcode

## 刷题方法
- 如何科学刷题？[阅读](https://leetcode.cn/circle/discuss/RvFUtj/)
- [LeetCode Rating GitHub](https://github.com/zhang-wangz/LeetCodeRating)

## 常见算法

### 贪心算法 (Greedy)
- [300. 最长递增子序列 (LIS)](https://leetcode.cn/problems/longest-increasing-subsequence)

### 回溯 (Backtracking)
- 回溯三问：
  1. 当前操作？
  2. 子问题？
  3. 下一个子问题？

### 动态规划 (DP)
#### 1. 一维数组
- **返回 dp[n-1]**
  - [70. 爬楼梯](https://leetcode.cn/problems/climbing-stairs/)
  - [198. 打家劫舍](https://leetcode.cn/problems/house-robber/)
- **返回 sum(dp)**
  - [413. 等差数列划分](https://leetcode.cn/problems/arithmetic-slices/description/)

#### 2. 二维数组
- **返回 max(dp)**
  - [221. 最大正方形](https://leetcode.cn/problems/maximal-square/)
- **边界条件处理**：
  - case 1: `i == 0 && j == 0`
  - case 2: `i == 0`
  - case 3: `j == 0`
  - case 4: `i != 0 && j != 0`
  - [64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)

#### 3. 分割类型
- 状态方程通常依赖于满足分割条件的位置
  - [279. 完全平方数](https://leetcode.cn/problems/perfect-squares/)
  - [139. 单词拆分](https://leetcode.cn/problems/word-break/)
  - [1105. 填充书架](https://leetcode.cn/problems/filling-book-shelves/)
  - [2369. 检查数组是否存在有效划分](https://leetcode.cn/problems/check-if-array-can-be-divided-into-subarrays/)
  - [1416. 恢复数组](https://leetcode.cn/problems/recover-array/)
  - [1043. 分隔数组以得到最大和](https://leetcode.cn/problems/partition-array-for-maximum-sum/)

#### 4. 背包问题
- **选或不选**（0-1 背包、完全背包、变形）
  - 0-1 背包：
    - `dfs(i, c) = max(dfs(i-1, c), dfs(i-1, c - weight[i]) + values[i])`
  - 常见变形：
    - 至多装 `capacity`：求方案数 / 最大价值
    - [恰好装 `capacity` ]：求方案数 / 最大/最小价值
      - [494. 目标和](https://leetcode.cn/problems/target-sum/)
    - 至少装 `capacity`：求方案数 / 最小价值

#### 5. 复杂度分析
- **状态个数** × **单个状态的计算时间**

#### 6. 边界条件处理
- 例如：[198. 打家劫舍](https://leetcode.cn/problems/house-robber/)：
  - 初始 `dp = [0] * (n + 2)`，避免越界

#### 7. 子序列问题
- [300. 最长递增子序列 (LIS)](https://leetcode.cn/problems/longest-increasing-subsequence)

#### 8. 二维数组的空间优化
- **滚动数组 (2*n)**：
  - [494. 目标和](https://leetcode.cn/problems/target-sum/)
- **倒序计算 (n)**：
  - [494. 目标和](https://www.bilibili.com/video/BV16Y411v7Y6)
- **用 `pre` 记录左上角的值 (n)**：
  - [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)

## 二分查找 (Binary Search)
- **左闭右开区间**
  循环条件 (l < r)
    记录最后一个满足条件的结果 res = mid;
    跳过 mid ，l = mid + 1;

## 思维方法总结

- **前后贪心：如 [542. 01矩阵](https://leetcode.cn/problems/01-matrix/) / [135. 分发糖果](https://leetcode.cn/problems/candy/)**
- **选或不选：如 背包问题，常见变形**
  - [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)
  - [198. 打家劫舍](https://leetcode.cn/problems/house-robber/)