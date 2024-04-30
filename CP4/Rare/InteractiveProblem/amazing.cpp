#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  int direc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  vector<string> mp = {"up", "down", "right", "left"};
  // 0 is unvisited, -1 is obstacle, 1 is visited
  unordered_map<int, unordered_map<int, int>> dist;
  dist[0][0] = 1;

  auto dfs = [&](auto &&f, int x, int y) {
    for (int i = 0; i < 4; i++) {
      auto &d = direc[i];
      int new_x = x + d[0];
      int new_y = y + d[1];
      if (dist[new_x][new_y] != 0) continue;
      cout << mp[i] << endl;
      cin >> s;
      if (s == "solved") return true;
      else if (s == "wall") continue;
      else {
        dist[new_x][new_y] = 1;
        bool can = f(f, new_x, new_y);
        if (can) return true;
        cout << mp[i ^ 1] << endl;
        cin >> s;
      }
    }
    return false;
  };

  bool found = dfs(dfs, 0, 0);
  if (!found) cout << "no way out" << endl;
}
