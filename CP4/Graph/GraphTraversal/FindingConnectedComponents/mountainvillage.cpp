#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<iii> viii;

int n, r, c, k;

int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

void solve() {
  cin >> r >> c;
  vector<vi> a(r, vi(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) cin >> a[i][j];
  }
  vi dist(r * c + 1, 1e9);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int mn = a[i][j], mx = mn, len = 0;
      auto comp = [](iii &a, iii &b) {
        auto &[d1, x1, y1] = a;
        auto &[d2, x2, y2] = b;
        return d1 > d2;
      };
      vector<vector<bool>> visited(r, vector<bool>(c));
      priority_queue<iii, viii, decltype(comp)> pq(comp);
      pq.emplace(0, i, j);
      while (!pq.empty()) {
        auto [d, x, y] = pq.top(); pq.pop();
        if (visited[x][y]) continue;
        mx = max(mx, d);
        visited[x][y] = true;
        len++;
        dist[len] = min(dist[len], mx - mn);
        for (auto &dir : direc) {
          int new_x = x + dir[0];
          int new_y = y + dir[1];
          if (new_x < 0 || new_x >= r || new_y < 0 || new_y >= c) continue;
          if (a[new_x][new_y] < mn) continue;
          pq.emplace(a[new_x][new_y], new_x, new_y);
        }
      }
    }
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> k;
    cout << dist[k] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
