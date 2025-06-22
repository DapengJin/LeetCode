# Leetcode

VS Code + LeetCode 插件 + Markmap 插件 for (.md)

The page below is copied from 思维导图.md 
Content here might be stale.
-----------------------------------------------

## 如何科学刷题？[here](https://leetcode.cn/circle/discuss/RvFUtj/)
- https://github.com/zhang-wangz/LeetCodeRating

## 指针
- 如果涉及头节点的操作就需要 dummy node
- [反转链表](https://www.bilibili.com/video/BV1sd4y1x7KN/)
  - [206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)
    - 循环 cur: while(cur)
    - 记录 cur->next: nxt = cur->next
    - 更新 cur->next: cur->next = pre
    - 移动 pre 和 cur: pre = cur; cur = nxt
  - [92. 反转链表 II](https://leetcode-cn.com/problems/reverse-linked-list-ii/)
    - p0 是反转链表的前一个节点
    - cur 最后指向的是 反转链表的后一个节点
    - p0的下一个节点的 next 指向 cur：p0->next->next = cur
    - p0 的 next 指向 pre：p0->next = pre
    - 用 dummy 节点简化代码，否则 p0 当 left == 1 时，不存在
    - 反转的时候一共有 right - left + 1 个节点
  - [25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)
    - 思路1: 快慢指针先找到要翻转的节点的尾部
    - 思路2: 先算出链表长度，然后每次翻转 k 个节点，直到剩余节点不足 k 个
    - 注意是否有节点被覆盖
  - 课后作业：
    - [24. 两两交换链表中的节点](https://leetcode.cn/problems/swap-nodes-in-pairs/)
      - 可以用 node0 node1 node2 三个节点来交换
    - 高位在链表尾 比较好添加 进位节点
      - [445. 两数相加 II](https://leetcode.cn/problems/add-two-numbers-ii/)
        - [2. 两数相加](https://leetcode-cn.com/problems/add-two-numbers/)
          - 递归 !!!修改原链表
          - 迭代 !!!新建链表
        - 逆序链表
      - [2816. 翻倍以链表形式表示的数字](https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/)
- [快慢指针](https://www.bilibili.com/video/BV1KG4y1G7cu/)
  - [876. 链表的中间结点](https://leetcode-cn.com/problems/middle-of-the-linked-list/)
    - 起始时 slow = fast = head
    - 奇数个节点时，fast会在尾部节点时，slow 在中间节点 （fast 一定会经过尾部节点）
    - 偶数个节点时，fast会在尾部节点的下一个节点时，slow 在中间节点的前一个节点（fast 一定会经过尾部节点的下一个节点）
  - [141. 环形链表](https://leetcode-cn.com/problems/linked-list-cycle/)
    - 快指针 相对于 慢指针，它的相对速度是每次循环走 1 步。一步一步走，如果有环，一定会遇上慢指针。
  - [142. 环形链表 II](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
    - head 到 入口的距离   为 a
      入口 到 相遇点 的距离 为 b
      相遇点 到 入口的距离  为 c
    环长 = b + c
    慢指针走了 a + b
    快指针走了 a + b + k(b + c)
    由于快指针移动的距离是慢指针的两倍：
        2(a + b) = a + b + k(b + c) 提出一个 b + c （环长）
        2a + 2b = a + 2b + c + (k-1)(b + c) 
        a - c = (k-1)(b + c)
        a - c 表示：从 h 走了 c 步 之后，到入口剩余的距离 是 环长的倍数
        所以，创建一个新的慢指针，从 h 出发。慢指针继续从和fast 的相遇点出发，当两个指针相遇时，就是入口
    当快慢指针相遇时，慢指针还没走完一整圈 （最坏情况：当慢指针在入口的时候，快指针刚好在慢指针的前面，他们相对速度为 1，所以 fast 需要走 环长 - 1 步才能和 slow 相遇）
- 快慢指针 + 反转链表 [143. 重排链表](https://leetcode-cn.com/problems/reorder-list/)
  - 找到中点
  - 反转后半部分
  - 合并两个链表 head 节点的尾部还是会指向mid，所以 reverse(mid) 的 节点数量一定小于等于 head 的节点数量
  - 课后作业：
    - [234. 回文链表](https://leetcode-cn.com/problems/palindrome-linked-list/)
    - [2130. 链表最大孪生和](https://leetcode.cn/problems/maximum-twin-sum-of-a-linked-list/)
- [删除链表](https://www.bilibili.com/video/BV1VP4y1Q71e/)
  - [237. 删除链表中的节点](https://leetcode-cn.com/problems/delete-node-in-a-linked-list/)】
    - 不能访问前一个节点，所以把下一个节点的值赋给当前节点，然后删除下一个节点
  - [19. 删除链表的倒数第 N 个结点](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)
    - 因为第一个节点可能被删除，所以需要 dummy 节点
    - 解1 递归: 
      递归可以算出倒数第 n+1 个节点的位置
    - 解2 快慢指针: 
      两个指针，一个先走 n 步，然后两个指针一起走，直到快指针走到尾部
  - [83. 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
    - 不需要 dummy 节点，因为可以保留前一重复的节点
  - [82. 删除排序链表中的重复元素 II](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
    - 需要比较 cur 后面两个节点的值，如果值相等 把 val 记录下来，然后删除所有值为 val 的节点

## 双指针
- 相向双指针 [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/) 带负数不能用滑动窗口
  - [167. 两数之和 II - 输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/)
    数组有序
    - [15. 三数之和](https://leetcode.cn/problems/3sum/)
      [18. 四数之和](https://leetcode.cn/problems/4sum/)
      利用 167 + 去重 (不仅，枚举第一个数时需要去重，双指针的时候也要去重)
  - [11. 盛最多水的容器](https://leetcode-cn.com/problems/container-with-most-water/)
    移动高度较大的指针没用，因为宽度减小，高度不可能增加。
  - [42. 接雨水](https://leetcode-cn.com/problems/trapping-rain-water/)
    假设 i-th 位置就是一个宽度是 1 的桶，这个桶的左边的高度就取决于左边的最大高度，右边同理。
  - [1004. 最大连续1的个数 III](https://leetcode.cn/problems/max-consecutive-ones-iii/)
    - follow up: the array is a circular array
      - 利用 % n
    - follow up2 - 不止 0 和 1，还有 -1, -1 是障碍物不能连起来
- 滑动窗口
  找的是 连续的子数组（sub-array） 就可以考虑滑动窗口
  但是，滑动窗口需要满足单调性，当右端点元素进入窗口时，窗口元素和是不能减少的。本题 nums 包含负数，当负数进入窗口时，窗口左端点反而要向左移动，导致算法复杂度不是线性的。
  - [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)
    用一个滑动窗口，维护一个区间，使得区间内的和大于等于 s
  - [713. 乘积小于K的子数组](https://leetcode-cn.com/problems/subarray-product-less-than-k/)
    判断 k <= 1 的情况
  - [3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
    用一个滑动窗口，维护一个区间，使得区间内的字符没有重复
  - [76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/)
    - less 维护目前子串中有 less 种字母的出现次数小于 t 中字母的出现次数。
  - 定长滑动窗口
    入 - 更新 - 出
  - 越长越合法型滑动窗口
    - 当右端点固定在 right 时，left 是刚好不满足的那个点，left 左边在 0,1,2,…,left−1 的所有子串都是满足要求的，这一共有 left 个，加到答案中。
    - [1358. 包含所有三种字符的子字符串数目](https://leetcode.cn/problems/number-of-substrings-containing-all-three-characters/)

## 二叉树
- 递归 数学归纳法 栈
  - 递：从原问题出发，把问题不断分解成更小的子问题，这就是递归中的「递」这个过程。
    不断「递」下去总会有个尽头，即递归的边界条件（base case）。
    直接返回它的答案就是「归」的开始。
- [104. 二叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)
  - 空间复杂度：递归的深度 最坏情况下是 O(n),树只有左儿子。
  - 可以 from bottom to top，也可以 from top to bottom 计算每一个节点的深度
  - [110. 平衡二叉树](https://leetcode-cn.com/problems/balanced-binary-tree/)
  - [199. 二叉树的右视图](https://leetcode-cn.com/problems/binary-tree-right-side-view/)
    - 解1: 右视图的话先遍历 右节点，记录每个节点的高度，维持最大高度 max_height，如果当前节点的高度大于 max_height，就加入结果集
    - 解2: 按层遍历 BFS，每层只取最右边的节点    
- [100. 相同的树](https://leetcode-cn.com/problems/same-tree/)
  - 判断是否相等的同时，判断左右子树是否相等
  - [101. 对称二叉树](https://leetcode-cn.com/problems/symmetric-tree/)
- [二叉搜索树](https://www.bilibili.com/video/BV14G411P7C1)
  - [98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/)
    - 前序遍历：中左右，递归的时候，需要传入上下界
    - 中序遍历：左中右，递归的时候，需要传入上一个节点的值（pre 不能放在参数里）
    - 后序遍历：左右中
      - 当前节点的值 是不在 左右节点的值 的范围内的。 [inf, -inf] 是空集，[-inf, inf] 是全集 表示 BST 不合法 之后的祖辈节点 也无法合法。 
      - 如果这个 节点的值 <= left_max 或者 >= right_min，就返回 false
      - 空节点返回 inf, -inf
      - 每个节点 都需要返回这个 子树 的最大值和最小值
      - 如果不是BST 就返回 -inf, inf
  - [510. 二叉搜索树中的中序后继 II](https://leetcode.cn/problems/inorder-successor-in-bst-ii/)
    - [直接看代码和图](./510.二叉搜索树中的中序后继-ii.cpp)
  - [285. 二叉搜索树中的中序后继](https://leetcode.cn/problems/inorder-successor-in-bst/)
    - 找比目标节点大的最小的节点
- [最近公共祖先](https://www.bilibili.com/video/BV1W44y1Z7AR/)
  - [236. 二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
    - 找到目标节点之后，就不用遍历 目标节点 的子树了。
      因为不管 另一个目标节点 在不在子树里，都不会影响最近公共祖先的位置。
      直接返回 root，当 root 为空的时候 也是直接返回 root
      if (root == nullptr ||
          root->val == p->val ||
          root->val == q->val)
        return root;
    - [235. 二叉搜索树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)
      - p 和 q 的值 在 root 两边的时候，root 就是最近公共祖先
      - p 和 q 的值 都在一边的时候，找这一边就行
- [二叉树的层序遍历](https://www.bilibili.com/video/BV1hG4y1277i/)
  - [102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
    - 用队列存储每一层的节点 ( pop 当前节点 push 不为空的 child )
    - 用一个变量记录每一层的节点数
    - while 循环直到队列为空
    - [103. 二叉树的锯齿形层序遍历](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)
      - 添加 bool 变量，奇数层 翻转
        if (odd) ranges::reverse(vals);
    - [513. 找树左下角的值](https://leetcode-cn.com/problems/find-bottom-left-tree-value/)
      - 解1: 用一个变量记录每一层的第一个节点
      - 解2 (prefer): 先入队右节点，再入队左节点，最后一个节点就是最左边的节点
      
## DFS
  - [339. 嵌套列表加权和](https://leetcode.cn/problems/nested-list-weight-sum/)
    - [364. 嵌套列表加权和 II](https://leetcode.cn/problems/nested-list-weight-sum-ii/)
      maxDepth 可以提出来的

## 回溯
- 模版：回溯三问
  - 当前操作？
  - 子问题？
  - 下一个子问题？ 
- 回溯 有一个增量构造答案的过程 这个过程通常用递归实现
- 递归不用思考很多层，只要边界条件和非边界条件的逻辑写对了，其他的交给 数学归纳法 就好了  
- [17. 电话号码的字母组合](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)
  - 原问题：构造长为 n 的字符串
  -  操作：枚举一个字母
  - 子问题：构造长为 n-1 的字符串

  全局数组 path 记录 路径中枚举的字母 
  - 当前操作：枚举 path[i] 要填入的字母
    ( 所以 dfs 的参数 也要有 i ) i 的含义是 >= i 的部分还需要枚举
  - 子问题：填入 path[i]
  - 下一个子问题：填入 path[i+1]

- [子集型](https://www.bilibili.com/video/BV1mG4y1A7Gu)
  每个元素都可以选或者不选
  - [78. 子集](https://leetcode.cn/problems/subsets/)
    - 解1：从 输入 角度 
      - 当前操作？枚举第 i 个数 选/不选
      - 子问题？     从下标 >= i   的数字中构造子集
      - 下一个子问题？从下标 >= i+1 的数字中构造子集
    - 解2：从 结果 角度
      枚举的 第一个数 选谁，枚举的 第二个数 选谁， ... （要避免重复
      - 当前操作？从 >= i 的下标中选一个数 j
      - 子问题？ 从 >= i 中构造子集
      - 下一个子问题？ 从 >= j+1 中构造子集
      - 每一个长度都可以是答案
    - [131. 分割回文串](https://leetcode.cn/problems/palindrome-partitioning/)
      - 解2：从 结果 角度
        枚举的 第一个数 选谁，枚举的 第二个数 选谁， ... （要避免重复
        - 当前操作？选择 回文字串 s[i,j] 加入 path
        - 子问题？      从下标 >= i   的后缀中构造回文分割
        - 下一个子问题？ 从下标 >= j+1 的后缀中构造回文分割
      - 解1：从 输入 角度 
        - 当前操作？枚举第 i 个逗号 选/不选
        - 子问题？      从下标 [start, i]   查看是否是 回文
        - 下一个子问题？ 从下标 [start, i+1] 和 [i+1, i+1] 查看是否是 回文
  - 课后作业
    - [257. 二叉树的所有路径](https://leetcode.cn/problems/binary-tree-paths/) 
      回溯+复习前面学的二叉树递归
      - string 的全局变量不好 pop(), 还是 多加个参数比较好写
      - 判断叶子节点可以用 if (node->left == node->right)
    - [113. 路径总和 II](https://leetcode.cn/problems/path-sum-ii/) 
      回溯+复习前面学的二叉树递归
      - 问：为什么递归参数 sum 不需要「恢复现场」？
        答：对于int这种基本类型的参数，在函数调用的时候会复制一份往下传递，sum += node->val 修改的仅仅是当前递归函数中的 sum 参数，并不会影响到其他递归函数中的 sum 。但是，如果把 sum 放在递归函数外，执行 sum += node->val 就会影响全局了，这种情况下是需要恢复现场的。

    - [784. 字母大小写全排列](https://leetcode.cn/problems/letter-case-permutation/)
      - 使用异或（^）操作符与空格字符（' '）可以实现大小写转换 c ^= ' ';
      - 解1: 选/不选
      - 解2: 选第几个
    - [LCP 51. 烹饪料理](https://leetcode.cn/problems/UEcfPD/)
      - 解1: 选/不选
      - 解2: 选第几个
    - ['2397'. 被列覆盖的最多行数](https://leetcode.cn/problems/maximum-rows-covered-by-columns/)
      - 解1: 选/不选
      - 解2: 选第几个
      - (未完成)[两种方法：二进制枚举 / Gosper's Hack（Python/Java/C++/Go）](https://leetcode.cn/problems/maximum-rows-covered-by-columns/solutions/1798794/by-endlesscheng-dvxe/)
    - [1239. 串联字符串的最大长度](https://leetcode.cn/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)
      - 解1: 选/不选
      - 解2: 选第几个
    - [2212. 射箭比赛中的最大得分](https://leetcode.cn/problems/maximum-points-in-an-archery-competition/)
      - 解1: 选/不选
      - 解2: 选第几个
      - vecter<vector<int>> res; res[0] = ? 和 res.push_back() 都是复制
    - [2698. 求一个整数的惩罚数](https://leetcode.cn/problems/find-the-punishment-number-of-an-integer/)
      - 选第几个
      - [306. 累加数](https://leetcode.cn/problems/additive-number/)
        - 防止溢出，string 直接相加
        - 选第几个
        - 如果有前导零，跳过这个子串
      - [93. 复原 IP 地址](https://leetcode.cn/problems/restore-ip-addresses/)
        - 选第几个

- [组合型](https://www.bilibili.com/video/BV1xG4y1F7nC)
  - [77. 组合](https://leetcode.cn/problems/combinations/solutions/2071017/hui-su-bu-hui-xie-tao-lu-zai-ci-pythonja-65lh/)
    - 选第几个
      - 可以倒着枚举 j 也可以表示还剩几个
      - 如果剩下的不够选就返回
    - 选/不选
    - 时间复杂度 k * C(n, k) 
      k 是拷贝答案的时间（递归到叶子复杂度是小于 k 的）
      C(n, k) 是叶子的个数
    - [216. 组合总和 III](https://leetcode.cn/problems/combination-sum-iii/solutions/2071013/hui-su-bu-hui-xie-tao-lu-zai-ci-pythonja-feme/)
      - 选第几个
      - 选/不选
      - 剪枝
        - 当 target < 0; 所选数之和已经超过 target
        - 当 target > (idx + idx - left + 1) * left / 2 
          后面都选 最大数 相加都加不到 target
  - [22. 括号生成](https://leetcode.cn/problems/generate-parentheses/solutions/2071015/hui-su-bu-hui-xie-tao-lu-zai-ci-pythonja-wcdw/)
    - 左括号的个数 >= 右括号的个数
    - 2n 个位置中 选 n 个位置 放左括号
    - 选/不选
      - 当前操作？枚举 path[i] 是左括号 还是 右括号
      - 子问题？     构造 字符串 >= i     的 部分
      - 下一个子问题？构造 字符串 >= i + 1 的 部分
    - 选第几个
  - 课后作业：
    - 按照视频中的要求，用另一种写法完成上面三题。
    - [301. 删除无效的括号](https://leetcode.cn/problems/remove-invalid-parentheses/)
    - [39. 组合总和](https://leetcode.cn/problems/combination-sum/)
      - 选/不选

- [排列型](https://www.bilibili.com/video/BV1mY411D7f6)
  - 46. 全排列 https://leetcode.cn/problems/permutations/
    - 解1: 在尚未访问过的 set 里面选
    - 解2: 把选到的（ [i , n) ）swap 到 i，再处理 [i + 1 , n)
  - [51. N 皇后](https://leetcode.cn/problems/n-queens/)
    - 不同行，不同列 => 每行每列恰好有一个皇后
    - 如何判断 是否对角线上有皇后？
      - 右上方向 row + col 是个定值 （范围是 [0, 2n-2]
      - 左上方向 row - col 是个定值 （范围是 [-(n-1), n-1]
        - 防止溢出 要加上 n-1
    - [52. N 皇后 II](https://leetcode.cn/problems/n-queens-ii/)
  - 课后作业：
    - [357. 统计各位数字都不同的数字个数](https://leetcode.cn/problems/count-numbers-with-unique-digits/)
      - 首位不要是 0
    - [2850. 将石头分散到网格图的最少移动次数](https://leetcode.cn/problems/minimum-moves-to-spread-stones-over-grid/)
      - 将 多余石头 的位置 存在 from
        将 没有石头 的位置 存在 to
        from 到 to 可以组成 1 对 1 映射
        这些映射的距离和就是答案
        需要把 from 全排列下 求出所有可能的 映射
  
## Greedy
- [300. 最长递增子序列 (LIS)](https://leetcode.cn/problems/longest-increasing-subsequence)


## DP
- 状态定义 / 状态转移方程
  - 定义 dfs / DP 数组含义时 他只能表示从一些元素中算出的结果 而不是从一个元素中算出的结果
- 启发思路：
  - 选/不选
  - 选第几个
- DP 三步
  - 思考回溯要怎么写
    - 入参和返回值
    - 递归到哪里
    - 递归的边界和入口
  - 改成记忆化搜索
  - 1:1 翻译成递推
- 复杂度
  - 状态个数 * 单个状态所需要的计算时间
- [从记忆化搜索到递推](https://www.bilibili.com/video/BV1Xj411K7oF)
  - 自顶向下算 == 记忆化搜索
  - 自底向上算 == 递推
  - 1:1 翻译成递推
    - dfs    -> f 数组
    - 递归    -> 循环
    - 递归边界 -> 数组初始值
  - [198. 打家劫舍](https://leetcode.cn/problems/house-robber/)
    - 模版：回溯三问
      - 当前操作？第 i 个房子选不选
      - 子问题？从前 i 个房子得到的最大金额和
      - 下一个子问题？ 
        - 不选 第 i 个房子：从前 i-1 个房子得到的最大金额和
        -  选 第 i 个房子：从前 i-2 个房子得到的最大金额和
        - dfs(i) = max(dfs(i-1), dfs(i-2) + nums[i])
    - 递归 f[i] = max(f[i-1], f[i-2] + nums[i]) 
      (f 的下标 i 可以同时加 2， 这样不会越界)
  - 课后作业：
    - [70. 爬楼梯][https://leetcode.cn/problems/climbing-stairs/]
    - [746. 使用最小花费爬楼梯](https://leetcode.cn/problems/min-cost-climbing-stairs/)
      - 你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯
        => f[0] = f[1] = 0; 爬到 0 或 1 无需花费
      - 动态规划有「选或不选」和「枚举选哪个」两种基本思考方式。在做题时，可根据题目要求，选择适合题目的一种来思考。本题用到的是「枚举选哪个」。
    - [377. 组合总和 Ⅳ](https://leetcode.cn/problems/combination-sum-iv/)
    - [2466. 统计构造好字符串的方案数 ](https://leetcode.cn/problems/count-ways-to-build-good-strings/)
      - 认真读题，提干是一次性插入 zero 个 0 或 one 个 1
    - [2266. 统计打字方案数](https://leetcode.cn/problems/count-number-of-texts/)
      - 解1: (222)(33)(7777) 把相同的连续字符切分
      - 加法原理: 加法是因为三种方案互斥
        - f[i] 表示 一次能爬 1-3 层 楼梯的表
          f[i] = f[i - 1] + f[i - 2] + f[i - 3]
        - g[i] 表示 一次能爬 1-4 层 楼梯的表 (字母 '7' 和 '9')
          g[i] = g[i - 1] + g[i - 2] + g[i - 3] + g[i - 4]
      - 乘法原理: 由于各个组（连续相同子串）的打字方案互相独立，
      根据乘法原理，把各个组的方案数相乘，即为答案。
      res = (f[3]) * (f[2]) * (g[4]) (三个2的方案数 * 两个3的方案数 * 四个7的方案数)
      - 解2: dfs + memorizition
    - (740. 删除并获得点数)[https://leetcode.cn/problems/delete-and-earn/]
      - 把 nums 转换成 !!!值域数组!!!
      - 上一个值和下一个值 都不能选
    - [213. 打家劫舍 II](https://leetcode.cn/problems/house-robber-ii/)
      - 需要分类讨论 选 nums[0] 还是不选
        - 选 nums[0]  , 就从下标 2 开始, 但是最后一个数不可以选
        - 不选 nums[0], 就从下标 1 开始,    最后一个数也可以选
    - [64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)
      - dfs(i,j)=min(dfs(i,j−1),dfs(i−1,j))+grid[i][j]
        - 递归边界：
          dfs(−1,j) = dfs(i,−1) = inf 
          dfs(0,0) == grid[0][0]
      - f[i][j] = min(f[i][j-1], f[i-1][j]) + grid[i][j]
        - 越界处理 i，j 同时 +1
        f[i+1][j+1] = min(f[i+1][j], f[i][j+1]) + grid[i][j]
      - 初始值 inf， 因为是从 f[1][1] 开始算的。
        可以把 f[0][1] 初始化为 0， 这样就不用 特别处理 f[1][1] = grid[0][0] 了
    - [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/) 
      - f[i] = max(f[i-1], 0) + nums[i] (如果 f[i-1] 都还没 0 大，就不选前面的了)
      - [152. 乘积最大子数组](https://leetcode.cn/problems/maximum-product-subarray/)
        f_max[i] = max({f_max[i - 1] * x, f_min[i - 1] * x, x});
        f_min[i] = min({f_max[i - 1] * x, f_min[i - 1] * x, x});

- 背包问题 [0-1背包 完全背包](https://www.bilibili.com/video/BV16Y411v7Y6)
  - 选或不选 （## 思想）
  - 0-1 背包
    dfs(i,c) = max(**dfs(i-1,c)**, dfs(i-1, c-weight[i]) + values[i])
    - [494. 目标和](https://leetcode.cn/problems/target-sum/solution/jiao-ni-yi-bu-bu-si-kao-dong-tai-gui-hua-s1cx/)
      - 将问题转化为 [恰好] 装 capacity，求 [方案数]
        - dfs(i, c) 的终止条件：
          if i < 0 (如果一个都不选的话) return 1 if c == 0 else 0 
          只有 dfs(-1, 0) 返回 1，其余都返回 0
        - f[0][0] = 1;
      - 空间优化
        - 滚动数组 % 2
        - 一维数组 倒序 更新 （因为要更新 c，c-weight[i]需要还未被更新）
      - 常见变形
        - [至少] 装 capacity，求 [方案数]
          - 所以 c < 0 都是满足条件的。
          - 那么 f[i][c-nums[i]] c-nums[i]是负数的时候放在哪呢？
             放在 f[i][0] 里面
          - dfs 的话，if i < 0: return 1 if c <= 0 else 0
          - capacity 至少是 0 的 情况下，每个物品都可以 选或不选 一共有 2^n 种方案
          - [demo](./494至少capacity.jpeg)
        - [至多] 装 capacity，求 [方案数]
          - dfs 的话，if i < 0 (如果一个都不选的话) return 1 
            都不选的话 所有 capacity 的方案都成立
          - DP 的话， 将第一排都初始化成 1 
      x
    - 课后作业：
      - [416. 分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)
        - 转化成 target 的问题
        - [474. 一和零](https://leetcode.cn/problems/ones-and-zeroes/)
          - 三维
        - [2787. 将一个数字表示成幂的和的方案数](https://leetcode.cn/problems/ways-to-express-an-integer-as-sum-of-powers/)
          - 解1: nums 含有 所有小于 n 的幂
            - 从 nums 里选 元素 以至于 它们的和 是 n
              => 完全背包问题
          - [灵神解法](https://leetcode.cn/problems/ways-to-express-an-integer-as-sum-of-powers/solutions/2354970/0-1-bei-bao-mo-ban-ti-by-endlesscheng-ap09/)
            - 空间优化成一维数组的解法 是不用知道 pow(i,x) 有多少个是 <= n 的
            - 直接返回最后一个就行
          - [279. 完全平方数](https://leetcode.cn/problems/perfect-squares/)
            - 同理 不用知道 i*i 有多少个是 <= n 的
            - 注意是正序遍历
            - [demo](./279.0-1demo.jpeg)
      - [2915. 和为目标值的最长子序列的长度](https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/)
        - [2915test](./2915test.jpeg)
        - 为什么 [494. 目标和] 就是 把矩阵 初始化成 0
          而本题需要 初始化成 -inf ?
          - 494 是求方案数的，要初始化成 0。(方案数最小也是 0 个方案)
            如果是恰好型背包并且要计算最大最小，那么初始值就和 inf 有关。


  - 完全背包 [322. 零钱兑换](https://leetcode.cn/problems/coin-change/)
    - 求最少钱币数量 init INT_MAX，f[0][0] = 0 (表示没有硬币可选，需要找零 0 元的时候，需要硬币的个数)
    - 组合型 回溯
    - dfs(i,c) =
                  max
                  (
                    dfs(i-1, c), // 完全不选 第 i 种 物品
                    dfs(i, c - weight[i]) + values[i] // 可以重复选 第 i 种 物品
                  )
      这里把之前的 i-1 变成了 i
    - [518. 零钱兑换 II](https://leetcode.cn/problems/coin-change-ii/)
      - 求 方案数 init 0，f[0][0] = 1 (表示没有硬币可选，需要找零 0 元的时候，有一种方案)
  - 常见变形
    - 至多装   capacity，求方案数   / 最大价值和
      - [14:42](https://www.bilibili.com/video/BV16Y411v7Y6)
    - [恰好]装 capacity，求[方案数] / 最大/最小价值和
      - [恰好] 装 capacity，求 [方案数] [494. 目标和](https://leetcode.cn/problems/target-sum/) （0-1 背包）
      dfs(i,c) = dfs(i-1,c) + dfs(i-1, c-weight[i])
      - [恰好] 装 capacity，求 [最小价值和] [322. 零钱兑换](https://leetcode.cn/problems/coin-change/) （完全背包）
      dfs(i,c) = min(**dfs(i-1,c)**， **dfs(i,c-coins[i]) + 1**) 
      （capacity 是面值， +1 是用了一枚硬币，要求最小的硬币数）
    - 至少装   capacity，求方案数   / 最小价值和



- [线性DP](https://www.bilibili.com/video/BV1TM4y1o7ug)
  - [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)
  两个字符串分别为 s 和 t
    - 启发思路：子序列 本质上就是 选/不选
      - 当前操作？s[i] 和 t[j] 选/不选
      - 当前问题？ s 的前 i 个字母 和 t 的前 j 个字母的 LCS 长度
      - 子问题？
        (s[i-1], t[j])         s[i] != t[j]
        (s[i], t[j-1])
        (s[i-1], t[j-1]) + 1   s[i] == t[j]
    - dfs(i, j) -> 最长 公共子序列 的长度
      - 终止条件 i < 0 || j < 0: return 0; 
      - 分类讨论 
        s[i] == t[j]: return dfs(i-1, j-1)
        s[i] != t[j]: return max(dfs(i-1, j), dfs(i, j-1))
    - 1:1 翻译成递推
      - f[i][j] = f[i-1][j-1] + 1              if s[i] == t[j]
                  max(f[i-1][j], f[i][j-1])    if s[i] != t[j]
      - init all 0
  - [72. 编辑距离](https://leetcode.cn/problems/edit-distance/)
    - dfs(i, j) -> 最少操作数 
      - 终止条件 i < 0 || j < 0: return abs(i-j)
      - 分类讨论 
        s[i] == t[j]: return dfs(i-1, j-1)
        s[i] != t[j]: return min(dfs(i-1, j), dfs(i, j-1), dfs(i-1)(j-1)) + 1
                                  删除 i         删除 j       替换 i 或 j
    - 1:1 翻译成递推
      - f[i][j] = f[i-1][j-1]                                   if s[i] == t[j]
                  min(f[i-1][j], f[i][j-1], f[i-1][j-1]) + 1    if s[i] != t[j]
      - init f[i][0] = i, f[j][0] = j; (可以在 for 循环中 init see [583. 两个字符串的删除操作] ) 
  - 课后作业：
    - [583. 两个字符串的删除操作](https://leetcode.cn/problems/delete-operation-for-two-strings/)
    - [72. 编辑距离] 简化版
      - [712. 两个字符串的最小ASCII删除和](https://leetcode.cn/problems/minimum-ascii-delete-sum-for-two-strings/)
        - 初始化 和 删除 的时候要加 s[i] or t[j]
      - [97. 交错字符串](https://leetcode.cn/problems/interleaving-string/)
        - 选 s1 还是选 s2
    - [1458. 两个子序列的最大点积](https://leetcode.cn/problems/max-dot-product-of-two-subsequences/)
      - 初始化：
        - 可以一个都不选 all 0
          f[i + 1][j + 1] = ranges::max({f[i][j + 1], f[i + 1][j], f[i][j] + v});
        - 不能是空      all -inf
          f[i + 1][j + 1] = ranges::max({f[i][j + 1], f[i + 1][j], f[i][j] + v, v});
    - [1092. 最短公共超序列](https://leetcode.cn/problems/shortest-common-supersequence/)
      - 根据 dp 表 倒推答案（找 f[i+1][j] 和 f[i][j+1] 中较小的那个）
      - [demo](./1092.demo.jpeg)
    - [10. 正则表达式匹配](https://leetcode.cn/problems/regular-expression-matching/)
                  / dfs(i  , j-2)  if p[j] == "*"                                       // 并未使用 "c*"
      dfs(i, j) =   dfs(i-1, j  )  if p[j] == "*" && (p[j-1] == s[i] || p[j-1] == '.')  // 使用 "c*" 或 ".*"
                  \ dfs(i-1, j-1)  if p[j] == "." || p[j] == s[i]                       // 使用 "."  或 字符可以匹配

- 子序列问题 [(20 线性DP)](https://www.bilibili.com/video/BV1ub411Q7sB)
  - [300. 最长递增子序列 (LIS)](https://leetcode.cn/problems/longest-increasing-subsequence)
    - 子集型回溯 n*n
      - ❌ 选/不选： 为了比较大小，需要知道上一个选的数字
      - ✅ 选哪个：  只需比较当前选的数字和下一个要选的数字
        - 当前操作：枚举比 nums[i] 小的 nums[j] 
          => j < i && nums[j] < nums[i] 
        - 当前问题：以 i 结尾的 LIS 的长度
        - 下个问题：以 j 结尾的 LIS 的长度
    - 解3 n*n : LIS = LCS(nums, 排序去重(nums))
    - 解4 greedy: 
      - f[i] 表示 末尾元素为 nums[i] 的 LIS 长度
      - g[i] 表示 长度为 i+1 的 IS 的 末尾元素的最小值
        - 修改一个数 lower_bound(g, x)
        - 末尾添加一个数
      - 若 LIS 中可以有相同元素呢？非严格递增
        - 改为 upper_bound
          相同的最大元素也要添加到屁股后面 like [1,2,2, ...]
        - [2826. 将三个组排序](https://leetcode.cn/problems/sorting-three-groups/)
        - [1964. 找出到每个位置为止最长的有效障碍赛跑路线](https://leetcode.cn/problems/find-the-longest-valid-obstacle-course-at-each-position/)   
          - 求 x 更新 g 时的 位置+1
  - 课后作业：
    
    1671. 得到山形数组的最少删除次数 https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/
    前后缀分解

    673. 最长递增子序列的个数 https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
    1626. 无矛盾的最佳球队 https://leetcode.cn/problems/best-team-with-no-conflicts/
    354. 俄罗斯套娃信封问题 https://leetcode.cn/problems/russian-doll-envelopes/
    1187. 使数组严格递增 https://leetcode.cn/problems/make-array-strictly-increasing/

- 处理边界值的方法
  - 一维数组
    - return dp[n-1]
      - [70. 爬楼梯](https://leetcode.cn/problems/climbing-stairs/)
      - [198. 打家劫舍](https://leetcode.cn/problems/house-robber/)
    - return sum(dp)
      - [413.](https://leetcode.cn/problems/arithmetic-slices/description/)

  - 二维数组
    - return max(dp)
      - [221. 最大正方形](https://leetcode.cn/problems/maximal-square/)
    - 边界条件的处理
      - case 1: i == 0 && j == 0
      - case 2: i == 0
      - case 3: j == 0
      - case 4 (else): i != 0 && j != 0
      - [64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)
    - 空间优化 
      - 循环顺序 [14:07](https://www.bilibili.com/video/BV16Y411v7Y6)
      - i:   --a1-- f(c) --a2--
        i+1: --a3-- f(c) --a4-- 
      - 倒序 (f(c) 取决于 a1 and a4)
        i: ----use----
                     c
        i+1:         ----use----
      - 正序 (f(c) 取决于 a2 and a3)
        i:             ----use----
                       c
        i+1: ----use----
      - 主要看需要的值 有没有被覆盖

- 分割类型
  - 动态规划的状态方程通常并 [不依赖于相邻] 的位置，
    而是依赖于满足分割条件的位置
  - [279. 完全平方数](https://leetcode.cn/problems/perfect-squares/)
  - [139. Word Break](./139.单词拆分.cpp)
  - [1105. 填充书架]
    [2369. 检查数组是否存在有效划分]
    [1416. 恢复数组]
    [1043. 分隔数组以得到最大和]

- 区间DP
  - 区别 
    - 线性DP：一般是在 前/后缀 上转移的
    - 区间DP：从小区间转移到大区间
  - 选或不选
    - 从两侧向内缩小规模
    - [516. 最长回文子序列](https://leetcode.cn/problems/longest-palindromic-subsequence/)
      - 解1：求 s 和 reversed(s) 的最长公共子序列 LCS
      - 解2：第一个字母选不选 和 最后一个字母选不选
        - eacbba
        - 因为 e != a，所以 e 和 a 不能都选 
        - $$
          dfs(i, j) =
          \begin{cases}
            dfs(i+1, j-1) + 2, & \text{如果 } s[i] = s[j] 
          \\
            \max(dfs(i+1, j), dfs(i, j-1)), & \text{如果 } s[i] \neq s[j]
          \end{cases}
          $$

          &emsp;当 \(i = j\) 时（字符串只有一个字符时）：
          $$
          dfs(i, i) = 1
          $$

          &emsp;当 \(i > j\) 时（无效区间）：
          $$
          dfs(i, j) = 0
          $$
        - [空间 O(n) 优化](https://leetcode.cn/problems/longest-palindromic-subsequence/solutions/2203001/shi-pin-jiao-ni-yi-bu-bu-si-kao-dong-tai-kgkg/)
  - 枚举选哪个
    - 分割成多个规模更小的字问题
    - [1039. 多边形三角剖分的最低得分](https://leetcode.cn/problems/minimum-score-triangulation-of-polygon)
    - $$f[i][j] = \max_{k=i+1}^{j-1}\{f[i][k] + f[k][j] + v[i] \times v[j] \times v[k]\}$$
    - $$f[i][j] = 0\;if\;j==i+1$$
  - [516. Longest Palindromic Subsequence](https://leetcode.cn/problems/longest-palindromic-subsequence/)
    - $$dp[i][j] = \bigcup_{k=i}^{j-1} \{l \, op \, r \mid l \in dp[i][k], \, r \in dp[k+1][j], \, op = ops[k] \}$$
    - $$dp[i][i] = \{nums[i]\}$$
    - 空间优化见：用 pre 记录左上角的值 

- 树形DP
  - 树的直径
    - 二叉树
      - [104. 二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)
      - 边权型 [543. 二叉树的直径](https://leetcode.cn/problems/diameter-of-binary-tree/)
      - 点权型 [124. 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)
    - 一般树
      - 一般树的性质 遍历所有 子节点，同时求最长和次长
      - 有向图：[2246. 相邻字符不同的最长路径](https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/)
      - 无向图：[1245. 树的直径](https://leetcode.cn/problems/tree-diameter/)
        对于无向图，可以通过记录父节点（dfs 多一个 parameter）然后在 dfs 时直接跳过父节点来避免重复访问。
  - 树上最大独立集 （最大独立集需要从图中选择尽量对的点，使这些点互不相邻）
    - 二叉树 337. 
    - 一般树 没有上司的舞会
  - 树上最小支配集
    - [968. 监控二叉树](https://leetcode.cn/problems/binary-tree-cameras/)
      相当于每个摄像头的 cost 为 1
    - 递归边界
      - 空节点 
        by_self = inf (空节点不能装摄像头)
        by_child = 0
        by_father = 0 (空节点不需要被监控)
    - 对于 cost 不为 1 的情况，把 1 改成对应的花费就好了
    - 简化公式 [保安站岗](https://www.luogu.com.cn/problem/P2458)
      - // 如果 root is monitored by_father, 他的 child 可以被 monitored by_self or by_child
      by_father = min(l_by_self, l_by_child) + min(r_by_self, r_by_child);
      - // 一定得有一个是 by_self 的，如果都选 by_self 的 （证明 by_self 的都比较小），min 一定是负值，和 0 取 max 就一定是 0
      by_child = by_father + max(0, min(l_by_self - l_by_child, r_by_self - r_by_child)); 
      - // 证明 by_child >= by_father
      by_self = min(l_by_self, l_by_father) + min(r_by_self,r_by_father) + 1;

- 边界条件的处理
  - [198. 打家劫舍](https://leetcode.cn/problems/house-robber/) 
    dp[i] = max(dp[i-1], dp[i-2] + nums[i])
    dp[i-2] 在 i==0 时，会 out-of-boundary。
    所以初始化的时候可以 dp = [0] * (n+2), 然后状态转移方程的 i 整体 +2
    [link](https://www.bilibili.com/video/BV1Xj411K7oF/)
  - [1105. 填充书架](https://leetcode.cn/problems/filling-bookcase-shelves/)



- 二维数组的空间优化
  - 滚动数组（2*n） dp[i%2][j]
    - [494. 目标和](https://leetcode.cn/problems/target-sum/)
  - 倒序计算 （n）
    - [494. 目标和](https://leetcode.cn/problems/target-sum/)
    [b站讲解 08:31](https://www.bilibili.com/video/BV16Y411v7Y6)
    [实现](./494.目标和.cpp)
    assume weight[i] = 2
    f(i,c) = f(i-1,c) + f(i-1, c-weight[i])
    => f[c] = f[c] + f[c-w[i]]
  - 用 pre 记录左上角的值 （n）
    - [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)
      - 去掉了数组的第一个维度
    - [516. Longest Palindromic Subsequence](https://leetcode.cn/problems/longest-palindromic-subsequence/)
      - 就是横竖遍历的区别，去掉了数组的第二个维度

- [状态机DP](https://www.bilibili.com/video/BV1ho4y1W7QK/)
  - [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)
    (k = 1)
    - 123 (k = 2) 
    - [122. 买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/solution/shi-pin-jiao-ni-yi-bu-bu-si-kao-dong-tai-o3y4/) 
      不限交易次数
      - 当前问题：到 i 天结束的时候，持有/未持有 股票的最大利润 分别是多少
        dfs(i, hold)  = return max(dfs(i-1, hold), dfs(i-1, !hold) - prices[i])
        dfs(i, !hold) = return max(dfs(i-1, !hold), dfs(i-1,hold) + prices[i])
        dfs(-1, hold) = -inf;
        dfs(-1, !hold) = 0; 
      - [309. 最佳买卖股票时机含冷冻期](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/solution/shi-pin-jiao-ni-yi-bu-bu-si-kao-dong-tai-0k0l/)
        带冷静期
        - 从 i-2 转移就好
      - [188. 买卖股票的最佳时机 IV](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/solution/shi-pin-jiao-ni-yi-bu-bu-si-kao-dong-tai-kksg/)
        至多 k 次
        - 既然有次数限制，应当在递归过程中记录 交易次数 j
          表示 i 天结束时 至多完成 j 笔操作
        - ⚠ 注意：买入 + 卖出才算一笔交易，不是两笔交易。
        - 状态转移方程：
          dfs(i, j, hold)  = max(dfs(i-1, j, hold), dfs(i-1, j-1, !hold) - prices[i])
          dfs(i, j, !hold) = max(dfs(i-1, j, !hold), dfs(i-1, j, hold) + prices[i])
        - 边界条件
          - dfs(*, -1, *) = -inf
          - dfs(-1, j, !hold) = 0; 
          - dfs(-1, j, hold) = -inf;
      - 恰好 k 次
        - f[0][1][0] = 0 （恰好完成 0 次交易时收益为 0 ） 其余 -∞
          （注意前面塞了个状态，f[0][1] 才恰好是完成 0 次的状态）
      - 至少 k 次
        - 至少 0 次 和 至少 -1 次是一样的，所以我们不需要插入状态
        - 至少 0 次 等价于 可以无限次交易， 所以 f[i][0][*] 的转移方程 和 122 是一样的
          f[i + 1][0][!hold] = max(f[i][0][!hold], f[i][0][hold] + p)
          f[i + 1][0][hold]  = max(f[i][0][hold], f[i][0][!hold] - p)  # 无限次
        - f[0][0][!hold] = 0，其余 -∞

  - 714
  - [256. 粉刷房子](https://leetcode.cn/problems/paint-house/)

## 单调栈
- 及时去掉无用数据
  保证栈中数据有序
- [739. 每日温度](https://leetcode.cn/problems/daily-temperatures)
  - 从左到右
  - 从右到左
- [42. 接雨水](https://leetcode.cn/problems/trapping-rain-water)
  - 单调下降的时候没办法接雨水
  - 一个桶需要两个边和一个底
  - 需要在栈里面找底和边 （找除了栈顶的 上一个更大的元素）
  - 面积 = (边的高度 - 底的高度) * 底的宽度
- 单调队列 [239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)
  - 及时去掉无用数据，保证双端队列有序
- 总结
  - 善用 递归 和 从右到左
  - 善于处理 空栈 （添加 inf）
  - 记得计算 未计算的结果 （强制所有元素出栈）
  - 课后习题
    - 单调栈
      - [496. 下一个更大元素 I](https://leetcode.cn/problems/next-greater-element-i)
      - [503. 下一个更大元素 II ](https://leetcode.cn/problems/next-greater-element-ii)
      circular: double the size and (% n)
      - [901. 股票价格跨度 ](https://leetcode.cn/problems/online-stock-span)
      添加 inf 就无需判断栈为空的情况
      - [1019. 链表中的下一个更大节点][https://leetcode.cn/problems/next-greater-node-in-linked-list]
      递归 可以同时实现，记录长度，从右往左遍历，和 记录当前节点的 index
      - [1944. 队列中可以看到的人数](https://leetcode.cn/problems/number-of-visible-people-in-a-queue/)
      从右到左
      [84. 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)
      1 添加 inf 就无需判断栈为空的情况
      2 需要把所有元素 (除了 inf) 都出栈计算面积
      - [1793. 好子数组的最大分数](https://leetcode.cn/problems/maximum-score-of-a-good-subarray/)
      上题的变形，k 要在长方形的 range 里
    - 单调队列
      1438. 绝对差不超过限制的最长连续子数组 https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
      2398. 预算内的最多机器人数目 https://leetcode.cn/problems/maximum-number-of-robots-within-budget/
      862. 和至少为 K 的最短子数组 https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/
      1499. 满足不等式的最大值 https://leetcode.cn/problems/max-value-of-equation/
      1696. 跳跃游戏 VI https://leetcode.cn/problems/jump-game-vi/
      2944. 购买水果需要的最少金币数 https://leetcode.cn/problems/minimum-number-of-coins-for-fruits/

## Binary Search (单调性是前提)
- 如果题目中有「最大化最小值」或者「最小化最大值」，一般都是二分答案，请记住这个套路。
- [红蓝染色法 bilibili](https://www.bilibili.com/video/BV1AP41137w7/)
  多种写法：[34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/solution/er-fen-cha-zhao-zong-shi-xie-bu-dui-yi-g-t9l9/)
  - 红色表示 false，即 小于    target。
  - 蓝色表示 true， 即 大于等于 target。
  - 循环不变量
    - L 的左边 始终是红色
    - R 的右边 始终是蓝色
    循环结束后 R + 1 等于 L，所以答案也可以用 L 表示。
  - 三种写法
    - [ ] 左闭右闭
    - [ ) 左闭右开
    - ( ) 左开右开 ✅ (默认，因为 l 和 r 直接等于 mid 就行，比较好写)
  - 四种情况 target = 8
    -   1 2 3 4 5 6 7 8 8 8 9 10
    - \>= lower_bound(target) 已实现 (第1个 8 )
    - \>  lower_bound(target + 1)   ( 9 )
    - <   lower_bound(target) - 1   ( 7 )
    - <=  lower_bound(target + 1)   (第3个 8 )
  - [69. x 的平方根](https://leetcode.cn/problems/sqrtx/)
    - 问：为什么代码返回的是 left？
      答：在练习二分时，请注意「求最小」和「求最大」的二分写法上的区别。
      「求最小」的题目和二分查找求「排序数组中某元素的第一个位置」是类似的，按照 红蓝染色法，左边是不满足要求的（红色），右边则是满足要求的（蓝色）。
      「求最大」的题目（例如本题）则相反，左边是满足要求的（蓝色），右边是不满足要求的（红色）。这会导致二分写法和「求最小」有一些区别。
  - 课后作业：
    - [2529. 正整数和负整数的最大计数](https://leetcode-cn.com/problems/maximum-count-of-positive-integer-and-negative-integer/)
    - [2300. 咒语和药水的成功对数](https://leetcode-cn.com/problems/successful-pairs-of-spells-and-potions/)
      - 1. 考虑整除和不整除两种情况
      - 2. 不想考虑小数
      - 3. 注意 判断 变量范围 以确保正确使用 long long 和 int
    - [2563. 统计公平数对的数目](https://leetcode-cn.com/problems/count-the-number-of-fair-pairs/)
      - 移项 lower <= nums[i] + nums[j] <= upper
        => lower - nums[j] <= nums[i] <= upper - nums[j]
      - 枚举 nums[j]，然后二分查找 nums[i] 的范围
    - [275. H 指数 II](https://leetcode-cn.com/problems/h-index-ii/)
      - 单调性
        - 如果至少有 2 篇论文的引用次数 >= 2，那么也必然至少有 1 篇论文的引用次数 >= 1
        - 如果没有 4 篇论文的引用次数 >= 4，那么也必然没有 5 篇论文的引用次数 >= 5
      - 二分的答案范围是 [0, n]，mid 就在 [0, n] 之间查找
    - [875. 爱吃香蕉的珂珂](https://leetcode-cn.com/problems/koko-eating-bananas/)
      - 二分答案范围是 [1, max(piles)]，mid 就在 [1, max(piles)] 之间查找
      - 二分查找的是吃香蕉的速度
      - 如何向上取整 (pile - 1) // speed + 1
    - [2187. 完成旅途的最少时间](https://leetcode.cn/problems/minimum-time-to-complete-trips/)
      - 可以求出 time_min，范围就是 [1, t_min * totalTrips]
      - (更优解) 求出 min max avg 可以缩小范围
    - [2861. 最大合金数](https://leetcode.cn/problems/maximum-number-of-alloys/)
      - 思路：
        1. 计算一台机器在 budget 内最多制造的合金数
        2. 计算 k 台机器在 budget 内最多制造的合金数
        3. 答案范围的下界可以是之前算好的 res
      - 如何计算 答案范围的最大值：假设
        1. 只需 一种金属
        2. 每次制造合金 这种金属之需要 1 个
        3. 这种金属的 cost 为 1
    - [2439. 最小化数组中的最大值](https://leetcode.cn/problems/minimize-maximum-of-array/)
      - 计算 extra 比计算 num_pre 好
    - [2517. 礼盒的最大甜蜜度](https://leetcode.cn/problems/maximum-tastiness-of-candy-basket/)
- [数组峰值 搜索旋转排序数组](https://www.bilibili.com/video/BV1QK411d76w/)

  - [162. 寻找峰值](https://leetcode.cn/problems/find-peak-element/solution/by-endlesscheng-9ass/)
    - 最后一个元素 n-1 必定是蓝色, 所以最后一个元素是不用分类的
    - 红色 代表 峰值左边 的数
    - 蓝色 代表 峰值 或 峰值右边 的数
  - [153. 寻找旋转排序数组中的最小值](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/solution/by-endlesscheng-owgd/)
    - 蓝色 代表 最小值 及 其右侧
    - 红色 代表 最小值左侧
    - 最后一个数一定是 蓝色，所以只用二分前面的数
    - 两种情况 [demo](./153.demo.jpeg)
      - 一个递增序列一个递增序列
      - 两个递增序列，且 start > end
      - 这两种情况，在 nums[mid] < end 时，
        nums[mid] 都是 最小值 或 最小值的右侧 （蓝色）
      - 在 nums[mid] > end 时，
        第一种情况不存在，
        第二种情况 一定在最小值的左侧（红色）
  - [33. 搜索旋转排序数组](https://leetcode.cn/problems/search-in-rotated-sorted-array/solution/by-endlesscheng-auuh/)
    - 蓝色 代表 target 及 其右侧
    - [demo](./33.demo.jpeg)
      - nums[mid] > end 
        target    > end &&    // target, nums[mid] 都在第一段 (case1 in demo)
        nums[mid] > target
      - nums[mid] <= end      // nums[mid] 在第二段
        target    > end ||    // target 在第一段，蓝色 (case2 in demo)
        nums[mid] > target    // target 也在同一段 && 满足 蓝色的定义 (case3 in demo)


- 左闭右开
  -  while (l < r) // 左闭右开区间不能寻找空集，所以没有等号
     res = mid; // 记录最后一个满足条件的结果
     l = mid + 1; // 因为左边是闭区间，当 mid 被 search 过之后应该被跳过
  - [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
    - 二分查找的时候，如果找到了 target，不要直接返回，而是继续查找，直到找到最左边的 target
    - 二分查找的时候，如果找到了 target，不要直接返回，而是继续查找，直到找到最右边的 target


## Priority Queue / Heap
- 实现 push() pop() size() top()
  - 满二叉树 (vector 实现)
    - 1-indexed 
    - left = 2*i, right = 2*i +1
    - parent = i / 2
  - siftDown(idx) 
    1. 用于提取 堆顶元素 pop() (交换 堆顶 和 堆尾 ...)
    2. 用于 buildQueue （从倒数第一个叶子的父亲开始 siftDown O(n) ）
  - bubbleUp(idx) 
    用于插入元素 push(x)
- [215. 数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/)
	-	最小堆  （Min Heap）：维持一个大小为 K 的堆，堆顶即第 K 大元素。
	-	快速选择（QuickSelect）：基于快速排序的 Partition 思想，O(n) 期望时间复杂度。
    - 第 k 大 ---> 第 n - k + 1 小 ---> index 第 n - k 的元素
    - Hoare partition
      外起步，先动步；  “外围启动，先动再判断”
      左跳小，右跳大；  “左边跳过小的，右边跳过大的”
      交换条件 i < j；
      终止返回是 j 点。
  - [703. 数据流中的第 K 大元素](https://leetcode.cn/problems/kth-largest-element-in-a-stream/)
    最小堆  （Min Heap）
  - [347. 前 K 个高频元素](https://leetcode.cn/problems/top-k-frequent-elements/)
    - 哈希表 + 最小堆：用 unordered_map<int, int> 统计频率，用最小堆维护前 K 个高频元素。
    - 桶排序
  - [23. 合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)
    - 弹出 堆顶 链表，再把 链表->next 放回去 if 不为空
- [253. 会议室 II](https://leetcode.cn/problems/meeting-rooms-ii/)
  - 最小堆
    - 开始时间排序
    - 堆里放结束时间
    - 如果会议已经结束 pop()
    - 添加当前会议
    - return q.size()
  - 扫描线 没看
- [373. 查找和最小的 K 对数字](https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/)
  - 若只添加 (sum, 0, 0) -> (1, 0) + (0, 1) -> (1, 1) + (1, 1) 如何去重？
    - ❌ 用 set 去重
    - ✅ 添加 (sum, i, 0) 出堆的时候 只用考虑 (i, j+1) 而不是 (i+1, j) 和 (i, j+1)


## Graph
- BFS source 寻找 target 的 最短路径
  - 总体 和 BFS 遍历 tree 一样
  - 唯一就是多了一个 visited 数组
  - 应该在 节点入队时就标记为 visited，这样可以避免重复入队
  - 双向 BFS
    - [127. 单词接龙](https://leetcode.cn/problems/word-ladder/)
      返回单词数目
  - BFS 反图 + DFS
    - [126. 单词接龙 II](https://leetcode.cn/problems/word-ladder-ii/)
      返回单词路径
— Dijkstra
  1. priority queue
  2. dist[0][0] = grid[0][0], 其他 INT_MAX
  3. 每次出最小 cost 的点拓展到 dist
  - 具体实现
    0. pop from pq
    1. lazy delete
    2. [update dis and pq] for all child (lazy relax)
  - [64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)
    - 如果 四个方向可移动 怎么办？Dijkstra
- 拓扑排序 Topological ordering
  和 BFS 一样，都有 queue
  queue 里面放的是入度为 0 的点。
  !!! 需要一个记录入度的数组
  - [210. 课程表 II](https://leetcode.cn/problems/course-schedule-ii/)

- Union Find
  - [305. 岛屿数量 II](https://leetcode.cn/problems/number-of-islands-ii/)
    - 给你一个图，突然有一些节点 从 1 变 0 了，有一些节点 从 0 变 1 了，有没有一种方法可以不用再跑一遍dfs就可以快速知道新的matrix有多少云。
      - 第一个pass把remove的cell值设为0，uf跑一遍图计算岛屿数量
        第二个pass只看add的，边add边计算岛屿数量


## 数学
- 最大公因数 (greatest common divisor, GCD)
  最小公倍数 (least common multiple  , LCM)
  - [辗转相除法](https://www.bilibili.com/video/BV1my4y1z7Zn/)
  [1979. 找出数组的最大公约数](https://leetcode.cn/problems/find-greatest-common-divisor-of-array/)
  a / b = c --- r
  (a, b) = (b, r) 直到 b == 0， a 就是最大公因数
  - 最小公倍数 = a * b / 最大公因数
- 质因数
  - [2507. 使用质因数之和替换后可以取到的最小值
](https://leetcode.cn/problems/smallest-value-after-replacing-with-sum-of-prime-factors/)
  - [2521. 数组乘积中的不同质因数数目](https://leetcode.cn/problems/distinct-prime-factors-of-product-of-array/)
- 质数 [2523. 范围内最接近的两个质数](https://leetcode.cn/problems/closest-prime-numbers-in-range)  [204. ]
  - 埃式筛
  - 线性筛（欧拉筛）每个合数只被划掉一次
    - 被他的 最小质因子 划掉
- 数字处理
  - 进制转换 504.
  -
- 整数边界
  - [7. 整数反转](https://leetcode-cn.com/problems/reverse-integer/)
    - 32 位有符号整数
    - 2147483647 2^31 - 1
    - -2147483648
    - (INT_MIN - digit) / 10 <= res <= (INT_max - digit) / 10 （小数）
    - 最后一位的 digit 不能超过 7（正数），8（负数），但是最后一位只能是 1 或者 2
    - 所以 res 推入 之前的范围可以优化到 INT_MIN // 10 < res < INT_MAX // 10

## [前缀和及其扩展](https://leetcode.cn/problems/range-sum-query-immutable/solutions/2693498/qian-zhui-he-ji-qi-kuo-zhan-fu-ti-dan-py-vaar/)
  - 303. 区域和检索 - 数组不可变](https://leetcode.cn/problems/range-sum-query-immutable/)
  - [560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)
    - 哈希表 + pre sum
  - [523. 连续的子数组和](https://leetcode.cn/problems/continuous-subarray-sum/)
    - 同余定理：如果两个整数 a, b 满足 a - b 能被 k 整除，那么 a 和 b 对 k 同余
      a % k = b % k => (a - b) % k = 0
  - [525. 连续数组](https://leetcode.cn/problems/contiguous-array/)
    哈希表 + pre sum (0, 1) 变成 (-1, 1)
  - [554. 砖墙](https://leetcode.cn/problems/brick-wall/)
    - 正难则反
      题目要求穿过的砖块数量最少，等效于通过的间隙最多。
    - 哈希表 + pre sum

## 字符串 string
- 枚举出所有的回文子串
  - [647. 回文子串](https://leetcode.cn/problems/palindromic-substrings/)
    - 中心拓展 O(n^2)
      注意 奇数 和 偶数 的区别
      可以用 l 和 r 来初始化中心
    - Manacher O(n)
      - 利用长回文串（box_m，box_r）的镜像信息 box_m - (i - box_m) = mirror
        镜像信息要注意不要越过 box_r 的边界，因为没有 box_r 右边的镜像信息。 
        => hl = min(box_r - i + 1, half_len[mirror])
      - 只有在 hl 被暴力拓展的时候（意味着 box_r 的边界被拓展）更新 box_m 和 box_r

## 珂朵莉树 / 动态开点线段树
- [2276. 统计区间中的整数数目](https://leetcode.cn/problems/count-integers-in-intervals/)

## 状态压缩
- 标记 index i: mask | (1 << i>>)
  查看 index i: (mask >> i) & 1
- [698. 划分为k个相等的子集](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/)
- [464. 我能赢吗](https://leetcode.cn/problems/can-i-win/)
## 多线程
- [1188. 设计有限阻塞队列](https://leetcode.cn/problems/design-bounded-blocking-queue/)
  - follow up:  multiput(List<T>) 方法不能与其他方法混合 items（即插入的 batch 必须连续）。
- [1117. H2O 生成](https://leetcode.cn/problems/building-h2o/)
## 思想 
  - 前后 greedy [ 542 | 135 ]
  - 选或不选
    - DP
      - 0-1 背包
      - 完全背包
      - 常见变形
      - [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)
  - 如何向上取整 ⌈pile / speed⌉ = (pile - 1) // speed + 1 
  - $ \lceil pile \div speed \rceil = \lfloor (pile - 1) \div speed \rfloor + 1 $
- [380. O(1) 时间插入、删除和获取随机元素](https://leetcode-cn.com/problems/insert-delete-getrandom-o1/)
  - unordered_map + vector
  	- •	Use a vector to store elements for O(1) random access.
	    •	Use an unordered_map to map values to their indices for O(1) removal. 
      remove 的时候，把最后一个元素和要删除的元素交换，然后删除最后一个元素
  - [432. 全 O(1) 的数据结构](https://leetcode.cn/problems/all-oone-data-structure/)
    - ✅
      unordered_map          -> counter {string : int}
      map(int, set<string>)  -> 排序 {frequency : set of strings}
      - 从原来的计数分组中移除 key，并在该组为空时删除该分组
        sort[count].erase(key)
        ... ...
    - unordered_map          -> {string : iter in list}
      list<int, set<string>> -> 排序 {frequency, set of strings}
      - 注意
        1. 更新 dict[key] = iter // 注意 iter 的有效性
        2. 从原来的计数分组中移除 key，并在该组为空时删除该分组
- [146. LRU 缓存](https://leetcode.cn/problems/lru-cache/)
  - doubled linked list + unordered_map<key, Node*> 
  - remove(node)
  - push_front(node)
  - get_node(node) -> node // 要更新 node 的位置 by remove 当前位置 和 push_front
- [716. 最大栈](https://leetcode.cn/problems/max-stack/)
  - 两个平衡树 (两个 set in cpp)
    设计的主要挑战是如何分别跟踪最大元素和最后一个元素。
    我们可以将所有元素都复制保留在两份堆栈中，一份是按照压入顺序排列的，另一份是按照元素的值排序的。
    - set<pair<int, int>> stack;  // {cnt, val}
      set<pair<int, int>> values; // {val, cnt}

- 使用异或（^）操作符与空格字符（' '）可以实现大小写转换
  - char ch = 'a';  // 小写字母
    ch ^= ' ';      // 通过异或空格字符来转换成大写字母
- 正难则反
  - [554. 砖墙](https://leetcode.cn/problems/brick-wall/)
    - 正难则反
      题目要求穿过的砖块数量最少，等效于通过的间隙最多。




## Parser
- LL(1) 就是“从左到右读，用最左推导，只看 1 个符号”的预测式解析。你的写法属于递归下降（Recursive-Descent），是实现 LL(1) 文法最直观的方式。
  - [772. 基本计算器 III](https://leetcode.cn/problems/basic-calculator-iii/)
  - [536. 从字符串生成二叉树](https://leetcode.cn/problems/construct-binary-tree-from-string/)
