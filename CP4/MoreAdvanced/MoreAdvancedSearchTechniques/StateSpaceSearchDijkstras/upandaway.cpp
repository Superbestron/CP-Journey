#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> iii;
const int INF = 1e9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x, k;
  cin >> n >> x >> k;
  vector<int> heights(n);
  vector<vector<int>> AL_cost(n, vector<int>(n));
  for (int i = 0; i < n; i++) cin >> heights[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> AL_cost[i][j];
  }
  vector<vector<int>> dist(n, vector<int>(k + 1, INF));
  dist[0][k] = 0;
  priority_queue<iii, vector<iii>, greater<>> pq;
  pq.emplace(0, 0, k);
  while (!pq.empty()) { // main loop
    auto [d, u, k_left] = pq.top();
    pq.pop(); // shortest unvisited u
    if (d > dist[u][k_left]) continue; // a very important check
    for (int v = 0; v < n; v++) { // C++17 style, w ignored
      if (u == v) continue;
      if (heights[v] > heights[u]) {
        int height_diff = heights[v] - heights[u];
        if (k_left < height_diff) continue;
        if (dist[v][k_left - height_diff] <= d + AL_cost[u][v]) continue;
        dist[v][k_left - height_diff] = d + AL_cost[u][v];
        pq.emplace(dist[v][k_left - height_diff], v, k_left - height_diff);
      } else {
        if (dist[v][k_left] <= d + AL_cost[u][v]) continue;
        dist[v][k_left] = d + AL_cost[u][v];
        pq.emplace(dist[v][k_left], v, k_left);
      }
    }
  }
  int mini = INF;
  for (int val : dist[x - 1]) mini = min(mini, val);
  cout << (mini == INF ? -1 : mini);
}