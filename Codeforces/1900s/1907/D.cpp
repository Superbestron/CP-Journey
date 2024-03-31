#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vii a(n);
  for (auto &[x, y] : a) cin >> x >> y;
  int lo = 0, hi = 1e9;
  auto can = [&](int x) {
    int mn = 0, mx = x;
    for (int i = 0; i < n; i++) {
      auto &[l, r] = a[i];
      mn = max(mn, l);
      mx = min(mx, r);
      if (mn > mx) return false;
      mn -= x; mx += x;
    }
    return true;
  };
  while (hi > lo) {
    int mid = lo + (hi - lo) / 2;
    can(mid) ? hi = mid : lo = mid + 1;
  }
  cout << lo << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
