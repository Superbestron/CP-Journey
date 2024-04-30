#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;

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
