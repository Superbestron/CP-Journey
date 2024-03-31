#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
int add_dir[2] = {-1, 1};
int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

void solve() {
  cin >> n;
  vector<string> a(2);
  for (auto &s : a) cin >> s;
  queue<ii> q;
  vector<vi> dist(2, vi(n, 1e9));
  dist[0][0] = 0;
  q.emplace(0, 0);
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (auto &dir : direc) {
      int new_x = x + dir[0];
      int new_y = y + dir[1];
      if (new_x < 0 || new_x >= 2 || new_y < 0 || new_y >= n) continue;
      char c = a[new_x][new_y];
      if (c == '<') new_y += add_dir[0];
      else new_y += add_dir[1];
      if (dist[new_x][new_y] != 1e9) continue;
      dist[new_x][new_y] = dist[x][y] + 1;
      q.emplace(new_x, new_y);
    }
  }
  if (dist[1][n - 1] != 1e9) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
