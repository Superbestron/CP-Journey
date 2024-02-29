#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<ll, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

int t, n, m;

void solve() {
  cin >> n >> m;
  vector<vii> AL(n);
  vi a(n);
  vector<vll> dist(n, vll(1001, 1e18));
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w; u--; v--;
    AL[u].emplace_back(v, w);
    AL[v].emplace_back(u, w);
  }
  for (int &i : a) cin >> i;
  priority_queue<iii, viii, greater<>> pq;
  pq.emplace(0, 0, a[0]);
  dist[0][a[0]] = 0;
  while (!pq.empty()) {
    auto [d, u, b] = pq.top(); pq.pop();
    if (d > dist[u][b]) continue;
    for (auto &[v, w] : AL[u]) {
      ll dt = (ll) b * w;
      int new_b = min(b, a[v]);
      if (dt + d >= dist[v][new_b]) continue;
      dist[v][new_b] = dt + d;
      pq.emplace(dt + d, v, new_b);
    }
  }
  ll ans = 1e18;
  for (ll i : dist[n - 1]) ans = min(ans, i);
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
