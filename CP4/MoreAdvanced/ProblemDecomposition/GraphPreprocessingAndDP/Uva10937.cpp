#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef tuple<int, int> ii;
typedef vector<int> vi;

vector<vi> memo;
vector<vi> AM;

int dp(int u, int mask) { // mask = free coordinates
  if (mask == 0) return AM[u][0]; // close the tour
  int &ans = memo[u][mask];
  if (ans != -1) return ans; // computed before
  ans = 1e9;
  int m = mask;
  while (m) { // up to O(n)
    int two_pow_v = LSOne(m); // but this is fast
    int v = __builtin_ctz(two_pow_v) + 1; // offset v by +1
    ans = min(ans, AM[u][v] + dp(v, mask ^ two_pow_v)); // keep the min
    m -= two_pow_v;
  }
  return ans;
}

int directions[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int direc[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int h, w;
  char arr[50][50];
  while (cin >> h >> w) {
    if (h == 0 && w == 0) break;
    vector<ii> points;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> arr[i][j];
        if (arr[i][j] == '@') points.emplace_back(i, j);
      }
    }

    bool can = true;

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (arr[i][j] == '!') points.emplace_back(i, j);
        if (arr[i][j] == '*') {
          for (auto &dir : directions) {
            int new_i = i + dir[0];
            int new_j = j + dir[1];
            if (new_i < 0 || new_i >= h || new_j < 0 || new_j >= w) continue;
            if (arr[new_i][new_j] == '*') continue;
            if (arr[new_i][new_j] == '@' || arr[new_i][new_j] == '!') can = false;
            arr[new_i][new_j] = '~';
          }
        }
      }
    }

    int p = points.size();
    AM.assign(p, vi(p, 1e9));

    for (int j = 0; j < p; j++) {
      vector<vi> dist(h, vi(w, 1e9));
      queue<ii> q;
      auto &[x, y] = points[j];
      dist[x][y] = 0;
      q.emplace(x, y);
      while (!q.empty()) {
        auto [x_u, y_u] = q.front(); q.pop();
        for (auto &dir : direc) {
          int new_i = x_u + dir[0];
          int new_j = y_u + dir[1];
          if (new_i < 0 || new_i >= h || new_j < 0 || new_j >= w) continue;
          if (arr[new_i][new_j] == '#' || arr[new_i][new_j] == '~') continue;
          if (dist[new_i][new_j] != 1e9) continue;
          dist[new_i][new_j] = dist[x_u][y_u] + 1;
          q.emplace(new_i, new_j);
        }
      }
      for (int k = j + 1; k < p; k++) {
        auto &[x_u, y_u] = points[k];
        AM[j][k] = AM[k][j] = dist[x_u][y_u];
      }
    }

    // Take note of these 2 edge cases
    if (!can) {
      cout << -1 << '\n';
      continue;
    } else if (p == 1) {
      cout << 0 << '\n';
      continue;
    }

    memo.assign(p, vector<int>(1 << (p - 1), -1));
    int ans = dp(0, (1 << (p - 1)) - 1);
    if (ans == 1e9) cout << -1 << '\n';
    else cout << ans << '\n';
  }
}
