#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k, curr_x, start;

void solve() {
  cin >> n >> k;
  vector<vi> AL(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  auto can = [&](int x) {
    int cnt = 0;
    auto dfs = [&](auto &&self, int u, int p) -> int {
      int sz = 1;
      for (int v : AL[u]) {
        if (v != p) {
          sz += self(self, v, u);
        }
      }
      if (sz >= x) {
        ++cnt;
        return 0;
      }
      return sz;
    };
    int sz = dfs(dfs, 0, -1);
    if (sz >= x) {
      ++cnt;
    }
    return cnt > k;
  };
  int lo = 1, hi = n / 2;
  while (hi > lo) {
    int mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
  cout << lo << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
