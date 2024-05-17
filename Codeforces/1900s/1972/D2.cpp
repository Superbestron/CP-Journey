#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, m;

void solve() {
  cin >> n >> m;
  ll ans = 0;
  vector<vi> bad(sqrt(n) + 1, vi(sqrt(m) + 1));  // gcd(a, b) > 1
  for (ll i = 2; i < min(sqrt(n), sqrt(m)); i++) {
    for (ll p = i; p * p < n; p += i) {
      for (ll q = i; q * q < m; q += i) bad[p][q] = true;
    }
  }
  for (ll p = 1; p * p < n; p++) {
    for (ll q = 1; q * q < m; q++) {
      if (bad[p][q]) continue;
      ans += min(n / p / (p + q), m / q / (p + q));
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
