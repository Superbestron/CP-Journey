#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, k;

void solve() {
  cin >> n >> k;
  vector<int> b(n);
  vector<vector<int>> AL(n, vector<int>());
  for (int &i : b) cin >> i;
  for (int i = 0; i < n - 1; i++) b.push_back(b[i]);
  for (int i = 0; i < n; i++) {
    int back = b[i + n - 1];
    if (back > n) continue;
    int backIdx = ((i + n - 1) - (back - 1) + n) % n;
    AL[i].push_back(backIdx);
  }
  vector<int> dist(n, 1e9);
  queue<int> q;
  q.push(0);
  dist[0] = 0;
  bool cycle = false;
  int max_dist = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : AL[u]) {
      if (dist[v] != 1e9) {
        cycle = true;
        break;
      }
      dist[v] = dist[u] + 1;
      max_dist = max(dist[v], max_dist);
      q.push(v);
    }
  }
  if (cycle) cout << "Yes\n";
  else if (max_dist >= k) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}