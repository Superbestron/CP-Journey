#include <bits/stdc++.h>
using namespace std;

int colors = 3;
string arr[4];
vector<vector<pair<int, int>>> coords(4, vector<pair<int, int>>());
vector<vector<int>> dist;
vector<vector<bool>> visited;
vector<char> s{'R', 'G', 'B', 'Y'};
char current;
int directions[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

inline pair<int, int> idx_to_c(int idx) {
  return make_pair(idx % 4, idx / 4);
}

void search_backtrack(int i, int j, int curr_dist) {
  for (auto& dir : directions) {
    int new_x = i + dir[0], new_y = j + dir[1];
    if (new_x < 0 || new_x == 4 || new_y < 0 || new_y == 4) continue;
    if (arr[new_x][new_y] != current || visited[new_x][new_y]) continue;
    visited[new_x][new_y] = true;
    dist[new_x][new_y] = max(curr_dist + 1, dist[new_x][new_y]);
    search_backtrack(new_x, new_y, curr_dist + 1);
    visited[new_x][new_y] = false;
  }
}

bool search() {
  visited.assign(4, vector<bool>(4, false));
  int total_dist = 0;
  dist.assign(4, vector<int>(4, -1e9));
  for (int i = 0; i < colors; i++) {
    dist[coords[i][0].first][coords[i][0].second] = 0;
    visited[coords[i][0].first][coords[i][0].second] = true;
    current = s[i];
    search_backtrack(coords[i][0].first, coords[i][0].second, 0);
    int curr_dist {dist[coords[i][1].first][coords[i][1].second]};
    if (curr_dist == -1e9) return false;
    total_dist += curr_dist;
  }
  return colors == 4 ? total_dist == 12 : total_dist == 13;
}

bool backtrack(int u) {
  if (u == 16) {
      return search();
  }
  const auto& [i, j] = idx_to_c(u);
  if (arr[i][j] == 'W') {
    for (char c : s) {
      arr[i][j] = c;
      if (backtrack(u + 1)) return true;
    }
    arr[i][j] = 'W';
  } else {
    if (backtrack(u + 1)) return true;
  }
  return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 4; i++) {
        cin >> arr[i];
        for (int j = 0; j < 4; j++) {
          if (arr[i][j] == 'R') {
            coords[0].emplace_back(i, j);
          } else if (arr[i][j] == 'G') {
            coords[1].emplace_back(i, j);
          } else if (arr[i][j] == 'B') {
            coords[2].emplace_back(i, j);
          } else if (arr[i][j] == 'Y') {
            colors = 4;
            coords[3].emplace_back(i, j);
          }
        }
    }
    if (backtrack(0)) cout << "solvable";
    else cout << "not solvable";
}

