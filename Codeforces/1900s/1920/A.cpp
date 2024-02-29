#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, a, x;

void solve() {
  cin >> n;
  vi v;
  int mn = -1, mx = 1e9, s = 0;
  for (int i = 0; i < n; i++) {
    cin >> a >> x;
    if (a == 1) {
      mn = max(mn, x);
    } else if (a == 2) {
      mx = min(mx, x);
    } else {
      v.push_back(x);
    }
  }
  for (int i : v) if (i >= mn && i <= mx) s++;
  cout << max(0, mx - mn + 1 - s) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
