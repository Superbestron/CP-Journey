#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, u, v, start;

inline void solve() {
  cin >> n >> t;
  vector<vi> AL(n);
  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    u--; v--;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  vi visited(n);
  auto dfs = [&](auto &&f, int u) -> bool {
    visited[u] = true;
    bool can_win = false;
    for (int v : AL[u]) {
      if (visited[v]) continue;
      can_win |= !f(f, v);
    }
    return can_win;
  };
  cin >> start; start--;
  cout << (dfs(dfs, start) ? "Ron" : "Hermione") << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
//  cin >> t;
//  while (t--) {
    solve();
//  }
}
