#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;
typedef tuple<int, int, int> iii;
typedef long long ll;
const int INF = 1e9;

// Honestly, question is unclear on whether the duo will take g-h if there are multiple shortest paths
// that go to dest. Turns out that they will ALWAYS take g-h if it is on any shortest path.

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tc, n, m, t, s, g, h, a, b, d;
  cin >> tc;
  while (tc--) {
    cin >> n >> m >> t >> s >> g >> h;
    s--; g--; h--;
    vector<vector<int>> dist( n, vector<int>(2, INF));
    vector<vector<ii>> AL(n);
    vector<int> dests(t);
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> d;
      a--; b--;
      AL[a].emplace_back(b, d);
      AL[b].emplace_back(a, d);
    }
    for (int &i : dests) {
      cin >> i;
      i--;
    }
    dist[s][0] = 0;
    priority_queue<iii, vector<iii>, greater<>> pq;
    pq.emplace(0, s, 0);
    while (!pq.empty()) { // main loop
      auto [d, u, taken_gh] = pq.top(); pq.pop(); // shortest unvisited u
      if (d > dist[u][taken_gh]) continue; // a very important check
      for (auto &[v, w] : AL[u]) {
        if (u == g && v == h || u == h && v == g) {
          if (dist[u][taken_gh] + w >= dist[v][1]) continue;
          dist[v][1] = dist[u][taken_gh] + w;
          pq.emplace(dist[v][1], v, 1);
        } else {
          if (dist[u][taken_gh] + w >= dist[v][taken_gh]) continue;
          dist[v][taken_gh] = dist[u][taken_gh] + w;
          pq.emplace(dist[v][taken_gh], v, taken_gh);
        }
      }
    }
    sort(dests.begin(), dests.end());
    for (int i : dests) {
      // if can reach dest in a shorter time if g-h is taken, it must have taken g-h
      if (dist[i][1] <= dist[i][0] && dist[i][1] != 1e9) cout << i + 1 << ' ';
    }
    cout << '\n';
  }
}
