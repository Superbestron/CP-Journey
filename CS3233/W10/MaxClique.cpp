#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;

int t, v, e;
vi AL;

inline void solve() {
  cin >> v >> e;
  AL.assign(v, 0);
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    AL[u] |= (1 << v);
    AL[v] |= (1 << u);
  }
  for (int i = 0; i < v; i++) {
    AL[i] |= (1 << i);
  }

  vi valid(1 << v);
  valid[0] = 1;
  int ans = 0;
  for (int i = 1; i < (1 << v); i++) {
    int lsb = LSOne(i);
    int j = __builtin_ctz (lsb );
    valid[i] = (valid[i - lsb]) && ((AL[j] & i) == i);
    if (valid[i]) ans = max(ans, __builtin_popcount(i));
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
