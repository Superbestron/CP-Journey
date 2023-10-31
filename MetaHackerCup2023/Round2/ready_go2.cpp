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
    int ans = 0;
    vector<string> v(R);
    vector<vector<bool>> visited(R, vector<bool>(C)), vis;
    for (int i = 0; i < R; i++) {
      cin >> v[i];
      for (int j = 0; j < C; j++) {
        if (v[i][j] == 'B') visited[i][j] = true;
      }
    }

    // choose where to insert
    vector<vector<int>> count(R, vector<int>(C));
    vis = visited;
    int dot_x, dot_y;
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (!vis[i][j] && v[i][j] == 'W') {
          int dot_count = 0, cnt = 1;
          vector<vector<bool>> dots_visited = visited;
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
              if (!dots_visited[new_x][new_y] && v[new_x][new_y] == '.') {
                dot_count++;
                dot_x = new_x, dot_y = new_y;
                dots_visited[new_x][new_y] = true;
              } else if (v[new_x][new_y] == 'W') {
                cnt++;
                vis[new_x][new_y] = true;
                q.emplace(new_x, new_y);
              }
            }
          }
          if (dot_count == 1) {
            count[dot_x][dot_y] += cnt;
          }
        }
      }
    }
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        ans = max(ans, count[i][j]);
      }
    }
    cout << "Case #" << tc << ": " << ans << '\n';
  }
}