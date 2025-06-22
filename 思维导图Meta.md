
## Communication
- drive through the problem 
- show your thought process
- ask questions 
- propose an initial solution, but also think  about its issues
- talk while coding. explain what you are doing.
- use examples to explain your approach
- be open about mistakes
- keep trying
- Listen hint from interviewer 
## Array
- partitioning, merging, slicing
- [498. 对角线遍历](https://www.1point3acres.com/bbs/thread-1117369-1-1.html)
- [303. 区域和检索 - 数组不可变](https://www.1point3acres.com/bbs/thread-1116963-1-1.html)
- prefix sum 
  - [560. 和为 K 的子数组](https://www.1point3acres.com/bbs/thread-1116630-1-1.html)
  - [348. 设计井字棋](https://www.1point3acres.com/bbs/thread-1114986-1-1.html)
- [643. 子数组最大平均数 I](https://www.1point3acres.com/bbs/thread-1116630-1-1.html)
- [209. 长度最小的子数组](https://www.1point3acres.com/bbs/thread-1116188-1-1.html)
  滑动窗口
- [88. 合并两个有序数组](https://www.1point3acres.com/bbs/thread-1116115-1-1.html)
- [349. 两个数组的交集](https://www.1point3acres.com/bbs/thread-1114986-1-1.html)


## Strings
- [!!!408. 有效单词缩写](https://www.1point3acres.com/bbs/thread-1118626-1-1.html)
- [!!!8. 字符串转换整数 (atoi)](https://www.1point3acres.com/bbs/thread-1118561-1-1.html)
  状态机
  - [demo](./8.demo.jpeg)
  - [65. 有效数字](https://www.1point3acres.com/bbs/thread-1117609-1-1.html)
- [680. 验证回文串 II](https://www.1point3acres.com/bbs/thread-1117286-1-1.html)
  - greedy 
  - s[i] != s[j] 时 查看 s[i+1, j] || s[i, j-1]
  - [1216. 验证回文串 III](https://www.1point3acres.com/bbs/thread-1117286-1-1.html)
    - 
- [249. 移位字符串分组](https://www.1point3acres.com/bbs/thread-1116967-1-1.html)
- [71. 简化路径](https://www.1point3acres.com/bbs/thread-1116429-1-1.html)
- [415. 字符串相加](https://www.1point3acres.com/bbs/thread-1115557-1-1.html)
  - followup 小数计算
    - 先算小数
    - 带着 carry 算整数 
- concatenate
  - +, append()
- contains
  - find()      返回子串的起始位置，如果找不到返回 std::string::npos
  - contains()  返回 true / false
- string -> int, int -> string 
  - stoi(), to_string()
- 大小写转换
  - ch ^= ' ';
## Binary Search
- 如果题目中有「最大化最小值」或者「最小化最大值」，一般都是二分答案，请记住这个套路。
- [410. 分割数组的最大值](https://www.1point3acres.com/bbs/thread-1117336-1-1.html)
  - [1011. 在 D 天内送达包裹的能力](https://www.1point3acres.com/bbs/thread-1117336-1-1.html)


## Sorting
- bubble sort
- merge sort
- [148. 排序链表](https://www.1point3acres.com/bbs/thread-1117368-1-1.html)
- [56. 合并区间](https://www.1point3acres.com/bbs/thread-1116784-1-1.html)
  - input is two sorted intervals A, B
    - 小的放在 res 里，merge A, B 里相对小的，res pop() 之前的
- 找出可以由一组数字digits（数字可能重复）组成的第二大整数
  - 先求出最大数， 然后吧最大数倒着的第一个和第二个不同的数字交换
  digits = {9, 8, 8, 7}
  最大整数: 9887
  次大整数: 9878

## Recursion
- choises
- superlatives: the most, the longest, all, ...
- divid and conquer
- trust and merge
  - turn a BST to a sorted linked list in place
    - trust left tree is a sorted linked and right tree is a sorted linked list.
    - merge the linked list together
- restore 回复现场
- 注意 basecases：nullptr，1 or 2 elements
- space complexity 
  O(depth)
- time complexity
  O(#braches ^ depth)
- [282. 给表达式添加运算符](https://www.1point3acres.com/bbs/thread-1118439-1-1.html)
  - 如何不通过 stack 完成 + 和 * 操作
    - 记录 之前加过的 最后一个数
    - 如果 有 * 操作，再把它 减 回去
  - 如何排除 heading 0 的 case
    - i == j // 只有一个数是 0 无所谓
    - || num[i] != 0 // 第一个数不是 0
- [301. 删除无效的括号](https://www.1point3acres.com/bbs/thread-1116967-1-1.html)



## Stack
- [!!!224. 基本计算器](https://www.1point3acres.com/bbs/thread-1117609-1-1.html)
- [1762. 能看到海景的建筑物](https://www.1point3acres.com/bbs/thread-1117336-1-1.html)



## Trees
- Binary Search Tree
  - in-order sorted
  - balanced
    - O(log(n))
  - un-balanced
    - worst case O(n)
- Tries
  - [!!!1233. 删除子文件夹](https://www.1point3acres.com/bbs/thread-1118649-1-1.html)
- [1650. 二叉树的最近公共祖先 III](https://www.1point3acres.com/bbs/thread-1118561-1-1.html) hash 
  - O(1) space 怎么办？
    - 同时向上遍历父节点：
      如果 p1 到达根节点后，转向 q 的初始位置。
	    如果 p2 到达根节点后，转向 p 的初始位置。
	  - 最终两个指针会在 LCA（最近公共祖先）相遇：
      由于两个指针会遍历相同的路径长度，所以它们要么相遇在 LCA，要么同时到达 nullptr（说明 p 和 q 不在同一棵树上）。
- [199. 二叉树的右视图](https://www.1point3acres.com/bbs/thread-1118649-1-1.html)
- [938. 二叉搜索树的范围和](https://www.1point3acres.com/bbs/thread-1118626-1-1.html)
- [314. 二叉树的垂直遍历](https://www.1point3acres.com/bbs/thread-1118439-1-1.html)
  - 只能用 BFS，因为 DFS 有可能 先访问更深的节点
- [543. 二叉树的直径](https://www.1point3acres.com/bbs/thread-1116784-1-1.html)
- [536. 从字符串生成二叉树](https://www.1point3acres.com/bbs/thread-1116784-1-1.html)
- [270. 最接近的二叉搜索树值](https://www.1point3acres.com/bbs/thread-1115557-1-1.html)





## Heaps / Priority Queue
- [215. 数组中的第K个最大元素](https://www.1point3acres.com/bbs/thread-1116784-1-1.html)
- [973. 最接近原点的 K 个点](https://www.1point3acres.com/bbs/thread-1115798-1-1.html)
## Graph
- DFS 不常用
- BFS
  - bi-directional BFS
- [127. 单词接龙](https://www.1point3acres.com/bbs/thread-1116337-1-1.html)
- [64. 最小路径和](https://www.1point3acres.com/bbs/thread-1115413-1-1.html)
  - 如果 四个方向可移动 怎么办？Dijkstra
## Greedy
- [650. 两个键的键盘]()


## DP
- [63. 不同路径 II](https://www.1point3acres.com/bbs/thread-1115038-1-1.html)

- [138. 随机链表的复制](https://www.1point3acres.com/bbs/thread-1119702-1-1.html)
- [125. 验证回文串](https://www.1point3acres.com/bbs/thread-1119702-1-1.html)

- https://www.1point3acres.com/bbs/thread-1119362-1-1.html
  - 14
  - 227
- https://www.1point3acres.com/bbs/thread-1119356-1-1.html
  - 246
  -
- https://www.1point3acres.com/bbs/thread-1119276-1-1.html
  - 921. 使括号有效的最少添加
  - 88. 
- 