#include <bits/stdc++.h>

using namespace std;
using ii = tuple<int, int>;
using iii = tuple<int, int, int>;
vector<vector<ii>> AL;
priority_queue<iii> pq;
int cost[1000][100], fuel[1000];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, T1, T2, D, Q, C, S, E;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> fuel[i];
  AL.assign(N, vector<ii>());
  for (int i = 0; i < M; i++) {
    cin >> T1 >> T2 >> D;
    AL[T1].emplace_back(T2, D);
    AL[T2].emplace_back(T1, D);
  }
  cin >> Q;
  while (Q--) {
    cin >> C >> S >> E;
    fill(cost[0], cost[0] + 1000 * 100, 1e9);
    cost[S][0] = 0;
    pq.emplace(0, S, 0);
    while (!pq.empty()) {
      auto [d, loc, left] = pq.top(); pq.pop();
      d = -d;
      if (d > cost[loc][left]) continue;
      // refuel
      if (left < C && d + fuel[loc] < cost[loc][left + 1]) {
        cost[loc][left + 1] = d + fuel[loc];
        pq.emplace(-cost[loc][left + 1], loc, left + 1);
      }
      for (auto& [v, w] : AL[loc]) {
        if (left < w) continue;
        if (d >= cost[v][left - w]) continue;
        cost[v][left - w] = d;
        if (v != E) pq.emplace(-cost[v][left - w], v, left - w);
      }
    }
    int min_cost = cost[E][0];
    if (min_cost == 1e9) cout << "impossible\n";
    else cout << min_cost << '\n';
  }
}
