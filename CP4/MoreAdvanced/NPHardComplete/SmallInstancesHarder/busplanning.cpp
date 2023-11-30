#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int n, k, c, ctr = 0;
unordered_map<string, int> str_to_int;
unordered_map<int, string> int_to_str;
string s, a, b;
vector<int> memo, AL, next_clique, next_mask, cliques;

int dp(int mask) {
  int& ans = memo[mask];
  if (ans != -1) return ans;
  if (mask == 0) return 0;
  ans = 18;
  for (int subset = mask; subset; subset = (mask & (subset - 1))) {
    if (__builtin_popcount(subset) > c) continue;
    bool can = true;
    int bm = subset;
    while (bm && can) {
      int b = __builtin_ctz(bm);
      bm -= 1 << b;
      can = ((AL[b] & subset) == subset);
    }
    if (!can) continue;
    int nmask = mask ^ subset;  // remaining not taken
    if (ans > 1 + dp(nmask)) {
      ans = 1 + dp(nmask);
      next_clique[mask] = subset;
      next_mask[mask] = nmask;
    }
  }
  return ans;
}

void fill_clique(int mask) {
  if (mask == 0) return;
  cliques.push_back(next_clique[mask]);
  fill_clique(next_mask[mask]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> k >> c;
  AL.assign(n, (1 << n) - 1);
  memo.assign(1 << n, -1);
  next_clique.assign(1 << n, -1);
  next_mask.assign(1 << n, -1);
  for (int i = 0; i < n; i++) {
    cin >> s;
    if (!str_to_int.count(s)) {
      int_to_str[ctr] = s;
      str_to_int[s] = ctr++;
    }
  }
  for (int i = 0; i < k; i++) {
    cin >> a >> b;
    AL[str_to_int[a]] &= ~(1 << str_to_int[b]);
    AL[str_to_int[b]] &= ~(1 << str_to_int[a]);
  }
  cout << dp((1 << n) - 1) << '\n';
  fill_clique((1 << n) - 1);
  for (auto &clique : cliques) {
    int mask = clique;
    while (mask) {
      int b = LSOne(mask);
      int idx = __builtin_ctz(mask);
      mask -= b;
      cout << int_to_str[idx] << ' ';
    }
    cout << '\n';
  }
}
