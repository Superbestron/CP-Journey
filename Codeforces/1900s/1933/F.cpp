#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;
int directions[2][2] = {{1, 0}, {0, 1}};

void solve() {
  cin >> n >> m;
  vector<vi> a(n, vi(m)), dist(n, vi(m, 1e9));
  queue<ii> q;
  vector<unordered_set<int>> AL(m);
  dist[0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      if (a[i][j] == 1) AL[j].insert(i);
    }
  }
  q.emplace(0, 0);
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (int i = 0; i < 2; i++) {
      auto &d = directions[i];
      int new_x = (x + d[0]) % n;
      int new_y = y + d[1];
      if (new_y < 0 || new_y >= m) continue;
      int dist_now = dist[x][y] + 1;
      int rock_pos = (new_x + dist_now % n) % n;
      if (AL[new_y].count(rock_pos)) continue;
      if (i == 0 && AL[new_y].count((n + rock_pos - 1) % n)) continue;
      if (dist[new_x][new_y] != 1e9) continue;
      dist[new_x][new_y] = dist_now;
      if (new_y == m - 1) continue;
      q.emplace(new_x, new_y);
    }
  }
  int ans = 1e9;
  for (int i = 0; i < n; i++) {
    int diff = abs(n - i - 1);
    ans = min(ans, diff + dist[i][m - 1]);
    ans = min(ans, n - diff + dist[i][m - 1]);
  }
  if (ans == 1e9) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
