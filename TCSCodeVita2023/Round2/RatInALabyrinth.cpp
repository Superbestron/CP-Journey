#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef tuple<int, int, int, int> iiii;
typedef vector<int> vi;

int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int M, N, T, x1, y1, x2, y2, CCs = 0, can = 0;
  cin >> M >> N >> T;
  vector<vi> dist(M, vi(N, -1));
  set<iiii> forbidden;
  for (int i = 0; i < T; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    x1 = min(x1, x2);
    x2 = max(x1, x2);
    y1 = min(y1, y2);
    y2 = max(y1, y2);
    if (x1 == x2) {
      for (int y = y1; y < y2; y++) {
        forbidden.emplace(x1 - 1, y, x1, y);
      }
    } else {
      for (int x = x1; x < x2; x++) {
        forbidden.emplace(x, y1 - 1, x, y1);
      }
    }
  }

  queue<ii> q;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (dist[i][j] != -1) continue;
      bool escape = false;
      CCs++;
      q.emplace(i, j);
      dist[i][j] = 0;
      while (!q.empty()) {
        ii t = q.front(); q.pop();
        int x = get<0>(t), y = get<1>(t);
        for (auto &d : direc) {
          int new_x = x + d[0];
          int new_y = y + d[1];
          iiii tup = make_tuple(min(x, new_x), min(y, new_y), max(x, new_x), max(y, new_y));
          if (new_x < 0 || new_x >= M || new_y < 0 || new_y >= N) {
            if (!forbidden.count(tup)) escape = true;
          } else {
            if (forbidden.count(tup)) continue;
            if (dist[new_x][new_y] != -1) continue;
            dist[new_x][new_y] = dist[x][y] + 1;
            q.emplace(new_x, new_y);
          }
        }
      }
      if (escape) can++;
    }
  }
  cout << round(100 * (double) can / CCs) << '\n';
}
