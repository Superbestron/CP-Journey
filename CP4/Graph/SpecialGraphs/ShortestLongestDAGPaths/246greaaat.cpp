#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Interesting technique of using vector of queues to simulate dijkstra to speed up
// runtime because range of values of dist is small.

const int INF = 1e9;
int N, T, min_cheer;
vi S, D, output, actions;

void cheers(int E) {
  if (E == 0) return;
  int idx = actions[E];
  cheers(E - S[idx]);
  output.push_back(idx + 1);
}

int main() {
  cin >> N >> T;
  S.assign(N + 1, 0);
  D.assign(N + 1, 0);
  S[0] = 1;
  D[0] = 1;
  for (int i = 1; i <= N; i++) {
    cin >> S[i] >> D[i];
    min_cheer = min(min_cheer, S[i]);
  }
  int mx = T - min_cheer;  // save on memory and runtime by putting a max cap of "dist" we can go
  actions.assign(mx + 1, 0);
  vector<queue<int>> q(T + 1);
  vi dist(mx + 1, INF);
  dist[0] = 0;
  q[0].push(0);

  // make sure queue[d] is empty before going to d + 1
  for (int d = 0; d <= T; d += q[d].empty()) {
    if (q[d].empty()) continue;
    int u = q[d].front(); q[d].pop();
    if (u == T) break;
    if (d > dist[u]) continue;

    for (int i = 0; i <= N; i++) {
      int v = u + S[i];
      if (v <= 0 || v > mx) continue;
      if (dist[v] <= dist[u] + D[i] || dist[u] + D[i] > T) continue;
      dist[v] = dist[u] + D[i];
      actions[v] = i;
      q[dist[v]].push(v);
    }
  }

  cheers(T);

  cout << output.size() << '\n';
  for (int i : output) cout << i << ' ';
  cout << '\n';
}
