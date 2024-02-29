#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, a, b;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<vector<pair<int, int>>> AL(n);
    vector<int> dist(n, -1);
    for (int i = 0; i < n - 1; i++) {
      cin >> a >> b;
      a--; b--;
      AL[a].emplace_back(b, i);
      AL[b].emplace_back(a, i);
    }
    queue<pair<int, int>> q;
    q.emplace(0, 1e9);
    dist[0] = 0;
    int ans = 0;
    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        auto [u, idxu] = q.front(); q.pop();
        for (auto& [v, idxv] : AL[u]) {
          if (dist[v] != -1) continue;
          if (idxv < idxu) dist[v] = dist[u] + 1;
          else dist[v] = dist[u];
          ans = max(dist[v], ans);
          q.emplace(v, idxv);
        }
      }
    }
    cout << ans << '\n';
  }
}