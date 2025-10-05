#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;

/*
1.深呼吸，不要紧张，慢慢读题，读明白题，题目往往比你想的简单。
  Take a deep breath, don't be nervous, read the question clearly, usually the question easier than you think.
2.暴力枚举:枚举什么，是否可以使用一些技巧加快枚举速度（预处理、前缀和、数据结构、数论分块）。
  Complete Search Enumeration: What to enumerate, is there a way to speed up the enumeration (pre-processing,
  prefix sum, data structure, number theory, etc.).
3.贪心:需要排序或使用数据结构（pq）吗，这么贪心一定最优吗。
  Greedy: Requires sorting or some sorted data structure (map, set, pq), is greedy the most optimal?
4.二分：满足单调性吗，怎么二分，如何确定二分函数返回值是什么。
  2 pointers: Is monotonicity satisfied, how to 2 pointer, what is the return value of the function?
5.位运算：按位贪心，还是与位运算本身的性质有关。
  Bit manipulation: Greedy bit-by-bit, or there is some properties related to the bit operations.
6.数学题：和最大公因数、质因子、取模是否有关。
  Mathematics: Related to GCD, prime factors, modulus, etc.
7.dp：怎么设计状态，状态转移方程是什么，初态是什么，使用循环还是记搜转移。
  DP: What states, transitions, initial states, use top-down or bottom-up.
8.搜索：dfs 还是 bfs ，搜索的时候状态是什么，需要记忆化吗。
  Search: DFS or BFS, what states during the search, do we need to memoise?
9.树上问题：是树形dp、树上贪心、或者是在树上搜索。
  Trees: Tree DP, greedy on trees, or search on trees?
10.图论：依靠什么样的关系建图，是求环统计结果还是最短路。
  Graph Theory: What properties do the graph have, cycles or shortest path?
11.组合数学：有几种值，每种值如何被组成，容斥关系是什么。
  Combinatorics: Several values, how each value is composed, and what is the inclusion-exclusion relationship.
12.交互题：log(n)次如何二分，2*n 次如何通过 n 次求出一些值，再根据剩余次数求答案。
  Interactive Problem: How to divide log(n) times into two pointers, how to find some values from 2*n times through n
  times, and then find the answer based on the remaining times.
13.如果以上几种都不是，多半是有一个 point 你没有注意到，记住正难则反。
  If it's not one of the above types, more than not you have missed out something. Try working backwards
*/

// Important points
// 1. String comparison
// if s1 and s2 is std::string
// s1 < s2 is by ascii ("dad" < "mom") == true
// else if s1 and s2 are char*/char[]
// s1 < s2 is by lexicographical order ("dad" < "mom") == false

vector<string> split(string &s, char delimiter) {
  size_t pos;
  string token;
  vector<string> arr;
  if (s.empty()) return arr;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    arr.emplace_back(token);
    s.erase(0, pos + 1);
  }
  arr.emplace_back(s);
  return arr;
}

class Compare {
 public:
  bool operator()(const pair<int, int> &o1, const pair<int, int> &o2) const {
    return o1.first == o2.first;
  }
};
class Compare2 {
 public:
  bool operator()(const pair<int, int> &o1, const pair<int, int> &o2) const {
    return o1.first < o2.first;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<string> v = split("Hello World!", ' ');

  auto comp = [](auto &a, auto &b) { return a.second > b.second; };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq2;
  set<pair<int, int>, decltype(comp)> s(comp);
  set < pair<int, int>, Compare2 > s2;
  s.insert(make_pair(1, 2));
  s2.insert(make_pair(1, 2));
  pq.emplace(1, 2);
  pq2.emplace(1, 2);

  // Binary Search
  int lo = 0, hi = 2e9;
  // variant 1
  while (hi > lo) {
    int mid = lo + (hi - lo) / 2;
    can(mid) ? hi = mid : lo = mid + 1;
  }
  // if want value to be saved
    while (hi >= lo) {
        int mid = lo + (hi - lo) / 2;
        if can(mid) {
            int ans = mid;
            hi = mid - 1;
        } else lo = mid + 1;
    }
  // variant 2
  while (hi > lo) {
    int mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
  //  double lo = 0, hi = 1000000;
  //  while (fabs(hi - lo) > EPS) {
  for (int i = 0; i < 50; ++i) {
    double mid = (lo + hi) / 2.0;
    can(mid) ? hi = mid : lo = mid;
  }

  // Measure Time
  // Start measuring time
  auto start = chrono::high_resolution_clock::now();
  // Stop measuring time
  auto end = chrono::high_resolution_clock::now();
  // Calculate duration
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  // Output the duration
  cout << "Execution time: " << duration.count() << " milliseconds" << '\n';

  // Backtracking
  // iterate all subsets technique O(3^n)
  int mask = 137; // (10001001)_2
  for (int ss = mask; ss; ss = (ss - 1) & mask) {  // new technique
    cout << ss << "\n"; // ss is a subset of mask
  }

  // iterate all ones of the bitmask
  for (int bm = mask; bm; bm -= LSOne(bm)) {
    int idx = __builtin_ctz(bm);
  }

  vi a;
  do {
    // iterate through all permutations
  } while (next_permutation(a.begin(), a.end()));
}

bool check_date(int day, int month, int year) {
  if (day == 0 || month == 0) return false;
  if (month > 12) return false;
  if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
    if (day > 31) return false;
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day > 30) return false;
  } else {
    bool leap;
    if (year % 400 == 0) {
      leap = true;
    } else if (year % 100 == 0) {
      leap = false;
    } else if (year % 4 == 0) {
      leap = true;
    } else {
      leap = false;
    }
    if (leap) {
      if (day > 29) return false;
    } else {
      if (day > 28) return false;
    }
  }
//    earliest += string(2 - min(2, (int) to_string(day).length()), '0') + to_string(day) + " "
//                + string(2 - min(2, (int) to_string(month).length()), '0') + to_string(month) + " "
//                + string(4 - min(4, (int) to_string(year).length()), '0') + to_string(year);
  return true;
}
