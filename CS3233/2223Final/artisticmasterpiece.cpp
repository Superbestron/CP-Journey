#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, r;
  string s;
  cin >> n >> r >> s;

  auto safe_sqrt = [&](ll x) {
    int y = sqrt(x);
    while ((y + 1) * (y + 1) <= x) y++;
    while (y * y > x) y--;
    return y;
  };

  vi rem(20, -1);
  for (int i = 0; i < 20; i++) {
    int val = r - i * i * i * i;
    if (val < 0) continue;
    rem[i] = safe_sqrt(val);
  }

  unordered_map<int, vector<ii>> fix_y;
  auto paint = [&](int xx, int yy) {
    for (int i = -19; i <= 19; i++) {
      if (rem[abs(i)] == -1) continue;
      fix_y[yy + i].emplace_back(xx - rem[abs(i)], 1);
      fix_y[yy + i].emplace_back(xx + rem[abs(i)] + 1, -1);
    }
  };

  int xx = 0, yy = 0;
  paint(xx, yy);
  for (auto c : s) {
    if (c == 'U') yy++;
    if (c == 'D') yy--;
    if (c == 'R') xx++;
    if (c == 'L') xx--;
    paint(xx, yy);
  }

  int ans = 0;
  for (auto [id, v] : fix_y) {
    sort(v.begin(), v.end());
    int curr = 0;
    for (int i = 0; i < (int) v.size() - 1; i++) {
      curr += v[i].second;
      if (curr >= 1) ans += (v[i + 1].first - v[i].first);
    }
  }

  cout << ans << '\n';
}
