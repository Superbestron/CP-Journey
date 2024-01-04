#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;
typedef tuple<double, int> di;

inline double cost(int a, int b, int h) {
  if (b < a) swap(a, b);
  return (a + b) * h * 0.02 / 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, a, b, h, start, end;
  vector<vector<ii>> stones;
  while (cin >> n) {
    if (n == 0) break;
    stones.assign(1001, {});
    for (int i = 0; i < n; i++) {
      cin >> a >> b >> h;
      stones[a].emplace_back(b, h);
      stones[b].emplace_back(a, h);
    }
    cin >> start >> end;
    priority_queue<di, vector<di>, greater<>> pq;
    vector<double> dist(1001, 1e9);
    dist[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
      auto [d, width] = pq.top(); pq.pop();
      if (d > dist[width]) continue;
      for (auto &[w, h1] : stones[width]) {
        double c = cost(width, w, h1);
        if (c + dist[width] >= dist[w]) continue;
        dist[w] = c + dist[width];
        pq.emplace(dist[w], w);
      }
    }
    cout << setprecision(2) << fixed << dist[end] << '\n';
  }
}
