#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> iii;
const int INF = 1e9 + 5;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, x, y, r;
  cin >> n;
  vector<vector<int>> AL(n);
  vector<iii> gears;
  for (int i = 0; i < n; i++) {
    cin >> x >> y >> r;
    for (int j = 0; j < gears.size(); j++) {
      auto& [x2, y2, r2] = gears[j];
      if ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) == (r + r2) * (r + r2)) {
        AL[i].push_back(j);
        AL[j].push_back(i);
      }
    }
    gears.emplace_back(x, y, r);
  }
  vector<int> dist(n, INF);
  queue<int> q;
  q.push(0);
  dist[0] = 1;
  int can = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u == n - 1) {
      can = 1;
      break;
    }
    for (int v : AL[u]) {
      if (dist[v] == INF) {
        dist[v] = (dist[u] == 1 ? 2 : 1);
        q.push(v);
      } else if (dist[v] == dist[u]) {  // same direction
        can = -1;
        goto done;
      }
    }
  }
  done:
  if (can == -1) cout << -1 << '\n';
  else if (can == 0) cout << 0 << '\n';
  else {
    int a = get<2>(gears[n - 1]);
    int b = get<2>(gears[0]);
    int div = gcd(a, b);
    a /= div; b /= div;
    b = (dist[0] == dist[n - 1] ? 1 : -1) * b;
    cout << a << " " << b << '\n';
  }
}