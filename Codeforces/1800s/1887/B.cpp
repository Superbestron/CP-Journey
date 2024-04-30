#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, t, m, k;

void solve() {
  cin >> n >> t;
  vector<unordered_map<int, vi>> AL(t);
  vector<set<int>> record_to_idx(t), node_exist_in_time(n);
  for (int i = 0; i < t; i++) {
    cin >> m;
    for (int j = 0; j < m; j++) {
      int u, v;
      cin >> u >> v; u--; v--;
      AL[i][u].push_back(v);
      AL[i][v].push_back(u);
      node_exist_in_time[u].insert(i);
      node_exist_in_time[v].insert(i);
    }
  }
  cin >> k;
  vi a(k), dist(n, 1e9);
  for (int i = 0; i < k; i++) {
    cin >> a[i]; a[i]--;
    record_to_idx[a[i]].insert(i);
  }

  priority_queue<ii, vii, greater<>> pq;
  pq.emplace(0, 0); // start at city 1 with dist 1
  dist[0] = 0;
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (int tm : node_exist_in_time[u]) {
      auto it = record_to_idx[tm].lower_bound(d);
      if (it == record_to_idx[tm].end()) continue;
      int time = *it;
      for (int v : AL[tm][u]) {
        if (dist[v] <= time + 1) continue;
        dist[v] = time + 1;
        pq.emplace(time + 1, v);
      }
    }
  }
  if (dist[n - 1] == 1e9) cout << -1 << '\n';
  else cout << dist[n - 1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
