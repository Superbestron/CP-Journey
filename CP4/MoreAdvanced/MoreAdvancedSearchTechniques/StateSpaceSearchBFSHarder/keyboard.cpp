#include <bits/stdc++.h>
using namespace std;

int directions[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int dist[50][50][10002];
char v[50][50];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int r, c;
  string s, te;
  cin >> r >> c;
  memset(dist, -1, sizeof dist);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) cin >> v[i][j];
  }
  cin >> te;
  te += '*';
  int initial = te.size();
  char prev = '+';
  for (char ch : te) {
    if (ch != prev) s += ch;
    prev = ch;
  }
  queue<tuple<int, int, int>> q;
  if (s[0] == v[0][0]) {
    dist[0][0][1] = 0;
    q.emplace(0, 0, 1);
  } else {
    dist[0][0][0] = 0;
    q.emplace(0, 0, 0);
  }

  while (!q.empty()) {
    auto &[ur, uc, us] = q.front(); q.pop();
    if (us == s.size()) {
      cout << dist[ur][uc][us] + initial;
      return 0;
    }
    for (int i = 0; i < 4; i++) {
      auto &dir = directions[i];
      char curr = v[ur][uc];
      int new_r = ur, new_c = uc;
      while (curr == v[ur][uc]) {
        new_r += dir[0];
        new_c += dir[1];
        if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) break;
        curr = v[new_r][new_c];
      }
      if (curr == v[ur][uc]) continue;
      if (v[new_r][new_c] == s[us]) {
        if (dist[new_r][new_c][us + 1] == -1) {
          dist[new_r][new_c][us + 1] = dist[ur][uc][us] + 1;
          q.emplace(new_r, new_c, us + 1);
        }
      } else {
        if (dist[new_r][new_c][us] == -1) {
          dist[new_r][new_c][us] = dist[ur][uc][us] + 1;
          q.emplace(new_r, new_c, us);
        }
      }
    }
  }
}