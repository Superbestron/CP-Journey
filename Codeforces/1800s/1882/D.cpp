#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int t, n;
vector<vi> AL;
vi a;
vector<ii> memo;

ii dp(int u, int p) {
  if (memo[u].first != -1) {
    return memo[u];
  }
  ll ans = 0, subtree = 1;
  for (int v : AL[u]) {
    if (v == p) continue;
    auto [cost, sz] = dp(v, u);
    subtree += sz;
    ans += cost;
    ans += (a[v] ^ a[u]) * sz;
  }
  memo[u] = {ans, subtree};
  return {ans, subtree};
}

void solve() {
  cin >> n;
  a.assign(n, 0);
  AL.assign(n, {});
  memo.assign(n, {-1, -1});
  for (int &i : a) cin >> i;
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  dp(0, 0);
  vll memo2(n);
  memo2[0] = memo[0].first;
  auto dfs = [&](auto &&f, int u, int p) -> void {
    for (int v : AL[u]) {
      if (v == p) continue;
      ll ori = memo2[u];
      auto &[temp, sz_btm] = memo[v];
      ll sz_top = n - sz_btm;
      ori += (sz_top - sz_btm) * (a[v] ^ a[u]);
      memo2[v] = ori;
      f(f, v, u);
    }
  };
  dfs(dfs, 0, 0);
  for (int i = 0; i < n; i++) cout << memo2[i] << ' ';
  cout << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
