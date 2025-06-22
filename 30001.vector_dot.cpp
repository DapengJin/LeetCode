#include "pkgs.h"
/** 
 * 给定一个包含多个相同值重复子序列的向量（例如：<5,5,5,6,6,6,6,3,3,3,9,9,8,8,8…>）        
 *     a) 设计一个更节省内存的向量表示。        b) 计算两个以节省内存格式编码的向量的点积*
 */

 using Run = pair<int,int>; // first = value, second = count

// 1. 从原始 vector 构造 RLE runs
vector<Run> encodeRLE(const vector<int>& nums) {
    vector<Run> runs;
    for (int x : nums) {
        if (runs.empty() || runs.back().first != x) {
            runs.emplace_back(x, 1);
        } else {
            runs.back().second++;
        }
    }
    return runs;
}

// 2. 对两个 RLE 向量计算点积
long long dotProductRLE(const vector<Run>& A, const vector<Run>& B) {
    int i = 0, j = 0;
    long long result = 0;
    // 复制可变的 count
    auto a = A;
    auto b = B;

    while (i < a.size() && j < b.size()) {
        // 最多可以匹配的重复次数
        int take = min(a[i].second, b[j].second);
        // 累加贡献 = valueA * valueB * 匹配次数
        result += 1LL * a[i].first * b[j].first * take;
        // 消耗这段 run
        a[i].second -= take;
        b[j].second -= take;
        // 如果某个 run 用完，就推进指针
        if (a[i].second == 0) ++i;
        if (b[j].second == 0) ++j;
    }
    return result;
}

int main() {
    vector<int> v1 = {5,5,5,6,6,6,6,3,3,3,9,9,8,8,8};
    vector<int> v2 = {5,5,6,6,6,3,3,9,8,8,8,8};

    auto r1 = encodeRLE(v1);  // [(5,3),(6,4),(3,3),(9,2),(8,3)]
    auto r2 = encodeRLE(v2);  // [(5,2),(6,3),(3,2),(9,1),(8,4)]

    long long dp = dotProductRLE(r1, r2);
    cout << "Dot product = " << dp << endl;
}