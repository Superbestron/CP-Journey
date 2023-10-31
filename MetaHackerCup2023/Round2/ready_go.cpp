#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, R, C;
  cin >> T;
  int directions[4][2] {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
  for (int tc = 1; tc <= T; tc++) {
    cin >> R >> C;
    vector<string> v(R);
    vector<vector<bool>> visited(R, vector<bool>(C)), vis;
    for (int i = 0; i < R; i++) {
      cin >> v[i];
      for (int j = 0; j < C; j++) {
        if (v[i][j] == 'B') visited[i][j] = true;
      }
    }

    for (int k = 0; k < R; k++) {
      for (int l = 0; l < C; l++) {
        // choose where to insert
        if (v[k][l] != '.') continue;
        v[k][l] = 'B';
        vis = visited;
        for (int i = 0; i < R; i++) {
          for (int j = 0; j < C; j++) {
            if (!vis[i][j] && v[i][j] == 'W') {
              bool can = true;
              queue<pair<int, int>> q;
              vis[i][j] = true;
              q.emplace(i, j);
              while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (auto& dir : directions) {
                  int new_x = x + dir[0], new_y = y + dir[1];
                  if (new_x < 0 || new_x == R || new_y < 0 || new_y == C) continue;
                  // can't capture
                  if (vis[new_x][new_y]) continue;
                  if (v[new_x][new_y] == '.') {
                    can = false;
                  } else if (v[new_x][new_y] == 'W') {
                    vis[new_x][new_y] = true;
                    q.emplace(new_x, new_y);
                  }
                }
              }
              if (can) {
                cout << "Case #" << tc << ": " << "YES\n";
                goto finish;
              }
            }
          }
        }
        v[k][l] = '.';
      }
    }
    cout << "Case #" << tc << ": " << "NO\n";
    finish:
    int x = 5;
  }
}