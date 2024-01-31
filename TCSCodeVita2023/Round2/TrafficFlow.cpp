#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, s1, s2, d1, d2;
  cin >> N >> M;
  int direc[2][2] = {{0, 1}, {1, 0}};
  vector<vi> v(N, vi(M));
  vector<vi> dist(N, vi(M, 1e9));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) cin >> v[i][j];
  }
  cin >> s1 >> s2 >> d1 >> d2;
  s1--; s2--; d1--; d2--;
  priority_queue<iii, vector<iii>, greater<iii>> pq;
  pq.emplace(0, s1, s2);
  dist[s1][s2] = v[s1][s2];
  while (!pq.empty()) {
    iii t = pq.top(); pq.pop();
    int d = get<0>(t), x = get<1>(t), y = get<2>(t);
    if (d > dist[x][y]) continue;
    for (auto &dir : direc) {
      int new_x = x + dir[0];
      int new_y = y + dir[1];
      if (new_x < 0 || new_x >= N || new_y < 0 || new_y >= M) continue;
      if (dist[x][y] + v[new_x][new_y] >= dist[new_x][new_y]) continue;
      dist[new_x][new_y] = dist[x][y] + v[new_x][new_y];
      pq.emplace(dist[new_x][new_y], new_x, new_y);
    }
  }
  if (dist[d1][d2] == 1e9) cout << -1 << '\n';
  else cout << dist[d1][d2] << '\n';
}
