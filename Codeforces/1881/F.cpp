#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, k, temp, a, b;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    vector<int> v(n);
    vector<bool> marked(n);
    vector<vector<int>> AL(n);
    for (int i = 0; i < k; i++) {
      cin >> temp;
      temp--;
      marked[temp] = true;
    }
    for (int i = 0; i < n - 1; i++) {
      cin >> a >> b;
      a--; b--;
      AL[a].push_back(b);
      AL[b].push_back(a);
    }
    if (k == 1) {
      cout << 0 << '\n';
      continue;
    }
    vector<int> dist(n, 1e9);
    queue<int> q;
    dist[0] = 0;
    q.push(0);
    int max_dist = 0, max_idx;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int o : AL[u]) {
        if (dist[o] != 1e9) continue;
        dist[o] = dist[u] + 1;
        if (marked[o] && dist[o] > max_dist) {
          max_dist = dist[o];
          max_idx = o;
        }
        q.push(o);
      }
    }
    dist.assign(n, 1e9);
    dist[max_idx] = 0;
    q.push(max_idx);
    max_dist = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int o : AL[u]) {
        if (dist[o] != 1e9) continue;
        dist[o] = dist[u] + 1;
        if (marked[o] && dist[o] > max_dist) {
          max_dist = dist[o];
          max_idx = o;
        }
        q.push(o);
      }
    }
    cout << (max_dist + 1) / 2 << '\n';
  }
}