#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
vector<pair<ll, int>> v;

int g(ll num) {
  return static_cast<int>(floorl(logl(num) / logl(floor(log2l(num)))));
}

inline void init() {
  vector<pair<ll, int>> r;
  for (int i = 2; i < 62; i++) {
    ll start = 1LL << i;
    ll end = (1LL << (i + 1)) - 1;
    int low = g(start), high = g(end);
    r.emplace_back(start, low);
    for (int j = low + 1; j <= high; j++) {
      ll left = r.back().first + 1, right = end;
      while (left < right) {
        ll mid = (left + right) / 2;
        if (g(mid) >= j) right = mid;
        else left = mid + 1;
      }
      r.emplace_back(left, j);
    }
  }
  int prev = -1;
  for (auto &[start, val] : r) {
    if (val != prev) v.emplace_back(start, val), prev = val;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, l, r;
  init();
  cin >> t;
  v.emplace_back(4e18, 0);
  while (t--) {
    cin >> l >> r;
    ll ans = 0;
    for (int i = 0; i < v.size() - 1 && l <= r; i++) {
      ll val = v[i].second;
      ll end = v[i + 1].first - 1;
      if (l > end) continue;
      ans += val * (min(r, end) - l + 1);
      ans %= MOD;
      l = end + 1;
    }
    cout << ans << '\n';
  }
}
