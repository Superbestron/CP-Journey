#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long double ld;

int n, m;

inline void solve() {
  cin >> n >> m;
  vector<vii> AL(n);
  vii edges;
  string ans(m, '0');
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    edges.emplace_back(u, v);
    AL[u].emplace_back(v, i);
    AL[v].emplace_back(u, i);
  }
  vi state(n);
  vector<bool> edges_visited(m);
  // 0 unvisited, 1 explored, 2 visited
  auto dfs = [&](auto &&f, int u) -> void {
    state[u] = 1;
    for (auto &[v, edge] : AL[u]) {
      if (edges_visited[edge]) continue;
      edges_visited[edge];
      if (edges[edge] == ii{u, v}) ans[edge] = '0';
      else ans[edge] = '1';
      if (state[v] == 0) {
        f(f, v);
      }
    }
  };
  for (int u = 0; u < n; ++u)
    if (state[u] == 0)
      dfs(dfs, u);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
