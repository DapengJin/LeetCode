// ∈ 
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <stack>
#include <unordered_set>
#include <queue>
#include <numeric>
#include <cfloat>    // 就能拿到 DBL_MAX
#include <limits.h>
#include <sstream>
#include <functional>
#include <set>
#include <list>

#include <shared_mutex>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <semaphore>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node {
    public:
        int val;
        Node* left;
        Node* right;
        Node* parent;
    };