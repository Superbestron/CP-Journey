#include <bits/stdc++.h>
using namespace std;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef pair<int, int> ii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int h, n, m;
  cin >> h >> n >> m;
  char arr[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> arr[i][j];
    }
  }

  if (h == 0) {
    cout << 0 << '\n';
    return 0;
  }

  vector<vi> dir_even = {{-1, 0}, {-1, -1}, {0, -1}, {0, 1}, {1, 0}, {1, -1}};
  vector<vi> dir_odd = {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
  vector<vb> visited(n, vb(m));
  queue<ii> q;
  vector<int> sizes;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (arr[i][j] == '#' || visited[i][j]) continue;

      int size = 1;
      visited[i][j] = true;
      q.emplace(i, j);

      while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        vector<vi> dir;
        if (x & 1) dir = dir_odd;
        else dir = dir_even;
        for (auto& d : dir) {
          int new_x = x + d[0];
          int new_y = y + d[1];
          if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
          if (arr[new_x][new_y] == '#' || visited[new_x][new_y]) continue;
          visited[new_x][new_y] = true;
          size++;
          q.emplace(new_x, new_y);
        }
      }

      sizes.push_back(size);
    }
  }

  sort(sizes.begin(), sizes.end(), greater());

  for (int i = 0; i < sizes.size(); i++) {
    h -= sizes[i];
    if (h <= 0) {
      cout << i + 1 << '\n';
      return 0;
    }
  }
}
