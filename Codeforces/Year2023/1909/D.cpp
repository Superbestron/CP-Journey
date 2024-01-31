#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

ll t, n, k;

void solve() {
  cin >> n >> k;
  vll v(n);
  bool all_zero = true, has_zero = false, has_neg = false, has_pos = false;
  for (ll &i : v) {
    cin >> i;
    i -= k;
    if (i < 0) {
      has_neg = true;
      all_zero = false;
    } else if (i > 0) {
      has_pos = true;
      all_zero = false;
    } else has_zero = true;
  }
  if (all_zero) cout << 0 << '\n';
  else if (has_zero || has_neg && has_pos) cout << -1 << '\n';
  else {
    ll g = 0, ans = 0;
    for (ll &i : v) g = gcd(g, abs(i));
    for (ll &i : v) ans += abs(i) / g - 1;
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
