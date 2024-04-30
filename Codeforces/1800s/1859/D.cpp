#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;
typedef vector<iiii> viiii;
typedef long long ll;

int t, n, q, x;

inline void solve() {
  cin >> n;
  viiii v(n);
  vii ranges;
  for (auto &[l, r, a, b] : v) cin >> l >> r >> a >> b;
  sort (v.begin(), v.end());
  for (int i = 0; i < n; i++) {
    auto &[l, r, a, b] = v[i];
    if (ranges.empty()) ranges.emplace_back(l, b);
    if (l > ranges.back().second) ranges.emplace_back(l, b);
    else ranges.back().second = max(ranges.back().second, b);
  }
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> x;
    auto it = lower_bound(ranges.begin(), ranges.end(), ii{x, 1e9});
    if (it == ranges.begin()) cout << x << ' ';
    else {
      it--;
      auto &[l, r] = *it;
      cout << max(x, r) << ' ';
    }
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
