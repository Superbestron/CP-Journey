#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

void solve() {
  cin >> n >> m;
  vll a(n), b(n), pref_b(m + 1);
  for (ll &i : a) cin >> i;
  for (ll &i : b) cin >> i;
  ll ans = 1e9;
  for (int i = 0; i < m; i++) {
    pref_b[i + 1] = pref_b[i] + b[i];
  }
  for (int i = 0; i < m; i++) {
    ans = min(ans, a[i] + pref_b[m] - pref_b[i + 1]);
  }

  for (int i = m; i < n; i++) {
    ans += min(a[i], b[i]);
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
