#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int M, N;
  cin >> M >> N;
  vector<vi> v(M, vi(N));
  vector<vi> direc(4), dist(M, vi(N, -1));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) cin >> v[i][j];
  }
  ii src, dest, move;
  cin >> get<0>(src) >> get<1>(src);
  cin >> get<0>(dest) >> get<1>(dest);
  cin >> get<0>(move) >> get<1>(move);
  int s1 = get<0>(src), s2 = get<1>(src);
  int d1 = get<0>(dest), d2 = get<1>(dest);
  int m1 = get<0>(move), m2 = get<1>(move);
  direc[0] = {m1, m2};
  direc[1] = {-m1, -m2};
  direc[2] = {m2, -m1};
  direc[3] = {-m2, m1};
  queue<ii> q;
  q.emplace(s1, s2);
  dist[s1][s2] = 0;
  while (!q.empty()) {
    ii t = q.front(); q.pop();
    int x = get<0>(t), y = get<1>(t);
    for (auto &d : direc) {
      int new_x = x + d[0];
      int new_y = y + d[1];
      if (new_x < 0 || new_x >= M || new_y < 0 || new_y >= N) continue;
      if (dist[new_x][new_y] != -1) continue;
      if (v[new_x][new_y] == 1) continue;
      dist[new_x][new_y] = dist[x][y] + 1;
      q.emplace(new_x, new_y);
    }
  }
  cout << dist[d1][d2] << '\n';
}
