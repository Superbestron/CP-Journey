#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

int t, n;
string s1, s2;

inline void solve() {
  unordered_map<string, int> mp;
  cin >> n;
  vii songs;
  vector<vi> AM(n, vi(n)), memo(n, vi(1 << n, -1));
  for (int i = 0; i < n; i++) {
    cin >> s1 >> s2;
    if (!mp.count(s1)) mp[s1] = mp.size();
    if (!mp.count(s2)) mp[s2] = mp.size();
    songs.emplace_back(mp[s1], mp[s2]);
  }
  for (int i = 0; i < n; i++) {
    auto &[idx1, idx2] = songs[i];
    for (int j = i + 1; j < n; j++) {
      auto &[idx3, idx4] = songs[j];
      if (idx1 == idx3 || idx2 == idx4) {
        AM[i][j] = AM[j][i] = 1;
      }
    }
  }
  auto dp = [&](auto &&f, int idx, int bm) {
    int &ans = memo[idx][bm];
    if (ans != -1) return ans;
    ans = 0;
    int mask = bm;
    while (mask) {
      int two_pow_v = LSOne(mask);
      int nxt_idx = __builtin_ctz(mask);
      if (AM[idx][nxt_idx]) {
        ans = max(ans, f(f, nxt_idx, bm ^ two_pow_v) + 1);
      }
      mask -= two_pow_v;
    }
    return ans;
  };
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int bm = (1 << n) - 1;
    bm ^= (1 << i);
    ans = max(ans, 1 + dp(dp, i, bm));
  }
  cout << n - ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
