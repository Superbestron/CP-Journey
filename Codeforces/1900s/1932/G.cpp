//#include <bits/stdc++.h>
//using namespace std;
//typedef long long ll;
//typedef vector<int> vi;
//typedef vector<ll> vll;
//typedef pair<int, int> ii;
//typedef vector<ii> vii;
//
//int t, n, m, H;
//
//void solve() {
//  cin >> n >> m >> H;
//  vector<vi> AL(n);
//  vi L(n), S(n), dist(n, 1e9);
//  for (int i = 0; i < m; i++) {
//    int u, v;
//    cin >> u >> v; u--; v--;
//    AL[u].push_back(v);
//    AL[v].push_back(u);
//  }
//  queue<int> q;
//  q.push(0);
//  int time = 0;
//  while (!q.empty()) {
//    int sz = q.size();
//    while (sz--) {
//      int u = q.front(); q.pop();
//      if (u == n - 1) {
//        cout << dist[u] << '\n';
//        return;
//      }
//      int u_level = L[u] + ((ll) (time % H) + (S[u] % H)) % H;
//      for (int v : AL[u]) {
//        int v_level = L[v] + ((ll) (time % H) + (S[v] % H)) % H;
//        if (u_level != v_level) continue;
//        if (dist[])
//        dist[v] = dist[u] + 1;
//      }
//    }
//    time++;
//  }
//}
//
//int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
//  cin >> t;
//  while (t--) {
//    solve();
//  }
//}
