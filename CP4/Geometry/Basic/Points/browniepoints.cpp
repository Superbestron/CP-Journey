#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  while (cin >> n) {
    if (n == 0) return 0;
    int median = n / 2;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      v.emplace_back(x, y);
    }
    int crossed_x = v[median].first, crossed_y = v[median].second;
    int stan = 0, ollie = 0;
    for (auto &[x, y] : v) {
      if (x == crossed_x || y == crossed_y) continue;
      if (x > crossed_x && y > crossed_y || x < crossed_x && y < crossed_y) stan++;
      else ollie++;
    }
    cout << stan << ' ' << ollie << '\n';
  }
}
