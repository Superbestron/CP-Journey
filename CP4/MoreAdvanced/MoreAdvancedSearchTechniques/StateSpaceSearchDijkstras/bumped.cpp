#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;
const ll INF = 1e18;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, f, s, t, k, l, c;
  cin >> n >> m >> f >> s >> t;
  vector<ll> dist(2 * n, INF);
  vector<vector<ii>> AL(2 * n);
  for (int i = 0; i < m; i++) {
    cin >> k >> l >> c;
    AL[k].emplace_back(l, c);
    AL[l].emplace_back(k, c);
    AL[k + n].emplace_back(l + n, c);
    AL[l + n].emplace_back(k, c);
  }
  for (int i = 0; i < f; i++) {
    cin >> k >> l;
    AL[k].emplace_back(l + n, 0);
  }
  dist[s] = 0;
  priority_queue<ii, vector<ii>, greater<>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) { // main loop
    auto [d, u] = pq.top();
    pq.pop(); // shortest unvisited u
    if (d > dist[u]) continue; // a very important check
    for (auto &[v, w] : AL[u]) { // C++17 style, w ignored
      if (dist[u] + w >= dist[v]) continue;
      dist[v] = dist[u] + w;
      pq.emplace(dist[v], v);
    }
  }
  cout << min(dist[t], dist[t + n]) << '\n';
}
