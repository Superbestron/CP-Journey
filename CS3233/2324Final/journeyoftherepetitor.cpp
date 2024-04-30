#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, m;
int direc[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
unordered_map<char, int> mp = {{'N', 0}, {'S', 1}, {'W', 2}, {'E', 3}};

inline void solve() {
  cin >> n >> m;
  vector<string> v(n);
  for (auto &s : v) cin >> s;
  vector<vi> visited(n, vi(m));
  vector<vii> states(n, vii(m));
  bool infinite = false;
  visited[0][0] = true;
  auto bfs = [&](auto &&f, int x, int y) {
    char c = v[x][y];
    int dir = mp[c];
    int new_x = (x + direc[dir][0] + n) % n;
    int new_y = (y + direc[dir][1] + m) % m;

    if (visited[new_x][new_y]) {
      auto [real_u, real_l] = states[x][y];
      auto [u, l] = states[new_x][new_y];
      if (c == 'N') real_u++;
      else if (c == 'S') real_u--;
      else if (c == 'W') real_l++;
      else real_l--;
      if (real_u == u && real_l == l) {
        infinite = true;
      }
      return;
    }

    visited[new_x][new_y] = true;
    auto [up, left] = states[x][y];
    if (c == 'N') states[new_x][new_y] = {up + 1, left};
    else if (c == 'S') states[new_x][new_y] = {up - 1, left};
    else if (c == 'W') states[new_x][new_y] = {up, left + 1};
    else states[new_x][new_y] = {up, left - 1};
    auto &[u, l] = states[new_x][new_y];

    f(f, new_x, new_y);
  };
  bfs(bfs, 0, 0);
  if (infinite) cout << 0 << '\n';
  else {
    cout << 1 << '\n';
    if (v[0][0] == 'N') cout << n << ' ' << 1 << ' ' << 'S' << '\n';
    else if (v[0][0] == 'S') cout << 2 << ' ' << 1 << ' ' << 'N' << '\n';
    else if (v[0][0] == 'W') cout << 1 << ' ' << m << ' ' << 'E' << '\n';
    else cout << 1 << ' ' << 2 << ' ' << 'W' << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
