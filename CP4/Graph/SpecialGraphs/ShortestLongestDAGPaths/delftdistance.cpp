#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<double, int, int> iii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<iii> viii;
typedef vector<double> vd;

int h, w;
vector<vi> dir1 = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<vi> dir2 = {{1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
vector<vi> dir3 = {{0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const double DIAG = M_PI * 10 / 4;

void solve() {
  cin >> h >> w;
  vector<string> a(h);
  vector<vd> dist(2 * h + 1, vd(2 * w + 1, 1e9));
  for (auto &s : a) cin >> s;
  dist[0][0] = 0;
  priority_queue<iii, viii, greater<>> pq;
  pq.emplace(0, 0, 0);
  while (!pq.empty()) {
    auto [d, x, y] = pq.top(); pq.pop();
    if (d > dist[x][y]) continue;
    if (x % 2 == 0 && y % 2 == 0) {
      for (auto &di : dir1) {
        int new_x = x + di[0];
        int new_y = y + di[1];
        if (new_x < 0 || new_x >= 2 * h + 1 || new_y < 0 || new_y >= 2 * w + 1) continue;
        double cost = 5;
        if (dist[new_x][new_y] <= dist[x][y] + cost) continue;
        dist[new_x][new_y] = dist[x][y] + cost;
        pq.emplace(dist[new_x][new_y], new_x, new_y);
      }
    } else if (x % 2 == 1) {
      for (int i = 0; i < dir2.size(); i++) {
        auto &di = dir2[i];
        int new_x = x + di[0];
        int new_y = y + di[1];
        if (new_x < 0 || new_x >= 2 * h + 1 || new_y < 0 || new_y >= 2 * w + 1) continue;
        int actual_x = x / 2, actual_y = new_y / 2;
        if (i >= 2 && a.at(actual_x).at(actual_y) == 'X') continue;
        double cost = i >= 2 ? DIAG : 5;
        if (dist[new_x][new_y] <= dist[x][y] + cost) continue;
        dist[new_x][new_y] = dist[x][y] + cost;
        pq.emplace(dist[new_x][new_y], new_x, new_y);
      }
    } else if (y % 2 == 1) {
      for (int i = 0; i < dir3.size(); i++) {
        auto &di = dir3[i];
        int new_x = x + di[0];
        int new_y = y + di[1];
        if (new_x < 0 || new_x >= 2 * h + 1 || new_y < 0 || new_y >= 2 * w + 1) continue;
        int actual_x = new_x / 2, actual_y = y / 2;
        if (i >= 2 && a.at(actual_x).at(actual_y) == 'X') continue;
        double cost = i >= 2 ? DIAG : 5;
        if (dist[new_x][new_y] <= dist[x][y] + cost) continue;
        dist[new_x][new_y] = dist[x][y] + cost;
        pq.emplace(dist[new_x][new_y], new_x, new_y);
      }
    }
  }
  cout << setprecision(6) << fixed << dist[2 * h][2 * w] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
