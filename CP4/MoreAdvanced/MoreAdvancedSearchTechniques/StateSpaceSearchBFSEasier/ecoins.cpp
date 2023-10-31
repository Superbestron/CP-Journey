#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s, a, b;
  cin >> n;
  while (n--) {
    cin >> m >> s;
    queue<pair<int, int>> q;
    int ans = 1;
    s *= s;
    vector<pair<int, int>> coins;
    unordered_map<int, unordered_set<int>> vis(90601);
    for (int i = 0; i < m; i++) {
      cin >> a >> b;
      coins.emplace_back(a, b);
      q.emplace(a, b);
      vis[a].insert(b);
    }
    bool can = false;
    while (!q.empty()) {
      ans++;
      int size = q.size();
      while (size--) {
        auto [x, y] = q.front(); q.pop();
        for (auto& coin : coins) {
          int new_x = x + coin.first;
          int new_y = y + coin.second;
          if (vis[new_x].count(new_y)) continue;
          vis[new_x].insert(new_y);
//          cout << new_x << ' ' << new_y << '\n';
          int sum = new_x * new_x + new_y * new_y;
          if (sum == s) {
            can = true;
            goto done;
          } else if (sum < s) q.emplace(new_x, new_y);
        }
      }
    }
    done:
    if (can) cout << ans << '\n';
    else cout << "not possible\n";
  }
}
