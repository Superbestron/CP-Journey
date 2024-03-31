#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;

int m, n, check;
unordered_map<string, int> mp;
vi AL, memo, next_clique, next_mask, cliques;
vector<string> names;

int dp(int mask) {
  int &ans = memo[mask];
  if (ans != -1) return ans;
  if (mask == 0) return 0;
  ans = 0;
  for (int subset = mask; subset; subset = (mask & (subset - 1))) {
    if (__builtin_popcount(subset) != 3) continue;
    int bm = subset;
    int test = 0;
    while (bm) {
      int b = __builtin_ctz(bm);
      bm -= 1 << b;
      test |= AL[b];
    }
    if (test != check) continue;
    int nmask = mask ^ subset;  // remaining not taken
    if (ans < 1 + dp(nmask)) {
      ans = 1 + dp(nmask);
      next_clique[mask] = subset;
      next_mask[mask] = nmask;
    } else if (ans == 1 + dp(nmask)) {
      int curr = next_clique[mask];
      if (curr < subset) {
        next_clique[mask] = subset;
        next_mask[mask] = nmask;
      }
    }
  }
  return ans;
}

void fill_clique(int mask) {
  if (mask == 0) return;
  bool can = __builtin_popcount(next_clique[mask]) == 3;
  if (!can) return;
  cliques.push_back(next_clique[mask]);
  fill_clique(next_mask[mask]);
}

inline void solve() {
  cin >> m >> n;
  check = (1 << m) - 1;
  names.assign(n, "");
  AL.assign(n, 0);
  for (int i = 0; i < m; i++) {
    string s;
    cin >> s;
    mp[s] = mp.size();
  }
  memo.assign(1 << n, -1);
  next_clique.assign(1 << n, -1);
  next_mask.assign(1 << n, -1);
  vector<pair<string, int>> temp(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    temp[i].first = s;
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> s;
      if (!mp.count(s)) continue;
      int idx = mp[s];
      temp[i].second |= (1 << idx);

    }
  }
  sort(temp.begin(), temp.end(), greater<>());
  for (int i = 0; i < n; i++) {
    names[i] = temp[i].first;
    AL[i] = temp[i].second;
  }
  cout << dp((1 << n) - 1) << '\n';
  fill_clique((1 << n) - 1);
  for (auto &clique : cliques) {
    int mask = clique;
    vector<string> output;
    while (mask) {
      int b = LSOne(mask);
      int idx = __builtin_ctz(mask);
      mask -= b;
      output.push_back(names[idx]);
    }
    reverse(output.begin(), output.end());
    for (auto &ou : output) cout << ou << ' ';
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
