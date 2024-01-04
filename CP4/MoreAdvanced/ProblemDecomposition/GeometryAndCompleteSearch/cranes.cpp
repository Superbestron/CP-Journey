#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;

int main() {
  int n, t;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<tuple<int, int, int>> v(n);
    for (int i = 0; i < n; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      v[i] = make_tuple(a, b, c);
    }

    int ans = 0;
    for (int bm = 0; bm < (1 << n); bm++) {
      bool valid = true;
      int cur = 0;
      for (int m = bm; m && valid; m -= LSOne(m)) {
        for (int q = m - LSOne(m); q; q -= LSOne(q)) {
          int a = __builtin_ctz(m);
          int b = __builtin_ctz(q);

          auto &[x1, y1, r1] = v[a];
          auto &[x2, y2, r2] = v[b];

          if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2)) {
            valid = false;
            break;
          }
        }
        auto &[x, y, r] = v[__builtin_ctz(m)];
        cur += r * r;
      }

      if (valid) ans = max(ans, cur);
    }
    cout << ans << '\n';
  }
}
