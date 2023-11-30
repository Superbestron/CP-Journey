#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int n, m;
unordered_map<string, int> str_to_int;
string a, b;
vector<int> memo, AL;

bool dp(int mask) {
  int& ans = memo[mask];
  if (ans != -1) return ans;
  if (mask == 0) return true;
  ans = false;
  for (int subset = mask; subset; subset = (mask & (subset - 1))) {
    if (__builtin_popcount(subset) != 3) continue;
    bool can = true;
    int bm = subset;
    while (bm && can) {
      int b = __builtin_ctz(bm);
      bm -= 1 << b;
      can = ((AL[b] & subset) == subset);
    }
    if (!can) continue;
    ans |= dp(mask - subset);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> m && m != 0) {
    n = 0;
    str_to_int.clear();
    AL.assign(15, 0);
    memo.assign(1 << 15, -1);
    for (int i = 0; i < m; i++) {
      cin >> a >> b;
      if (!str_to_int.count(a)) {
        AL[n] |= 1 << n;
        str_to_int[a] = n++;
      }
      if (!str_to_int.count(b)) {
        AL[n] |= 1 << n;
        str_to_int[b] = n++;
      }
      int a_idx = str_to_int[a], b_idx = str_to_int[b];
      AL[a_idx] |= 1 << b_idx;
      AL[b_idx] |= 1 << a_idx;
    }
    bool can = dp((1 << n) - 1);
    if (can) cout << "possible\n";
    else cout << "impossible\n";
  }
}
