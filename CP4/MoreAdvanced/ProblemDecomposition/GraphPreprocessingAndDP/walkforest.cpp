#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;

vector<int> dist, vt;
vector<vector<ii>> AL;
vector<vector<int>> AL2;

void toposort(int u) {
  dist[u] = 1;
  for (int v : AL2[u]) {
    if (dist[v] == 0) toposort(v);
  }
  vt.push_back(u);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, a, b, d;
  while (cin >> N) {
    if (N == 0) break;
    cin >> M;
    dist.assign(N, 1e9);
    AL.assign(N, {});
    AL2.assign(N, {});
    for (int i = 0; i < M; i++) {
      cin >> a >> b >> d;
      a--; b--;
      AL[a].emplace_back(b, d);
      AL[b].emplace_back(a, d);
    }

    priority_queue<ii, vector<ii>, greater<>> pq;
    dist[1] = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d > dist[u]) continue;
      for (auto &[v, w] : AL[u]) {
        if (d + w >= dist[v]) continue;
        dist[v] = d + w;
        pq.emplace(dist[v], v);
      }
    }

    for (int i = 0; i < N; i++) {
      for (auto &[v, w] : AL[i]) {
        if (dist[v] < dist[i]) {
          AL2[i].push_back(v);
        }
      }
    }

    vt.clear();
    dist.assign(N, 0);
    toposort(0);
    reverse(vt.begin(), vt.end());

    dist.assign(N, 0);
    dist[0] = 1;
    for (int i : vt) {
      for (int v : AL2[i]) {
        dist[v] += dist[i];
      }
    }

    cout << dist[1] << '\n';
  }
}
