#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, k;

void solve() {
  cin >> n >> k;
  vll a(n);
  for (ll &i : a) cin >> i;
  if (k >= 3) {
    cout << 0 << '\n';
    return;
  }
  sort(a.begin(), a.end());
  ll ans = a[0];
  for (int i = 1; i < n; i++) {
    ans = min(ans, a[i] - a[i - 1]);
  }

  if (k == 1) cout << ans << '\n';
  else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        ll v = a[i] - a[j];
        ll p = lower_bound(a.begin(), a.end(), v) - a.begin();
        if (p < n) ans = min(ans, a[p] - v);
        if (p > 0) ans = min(ans, v - a[p - 1]);
      }
    }
    cout << ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
