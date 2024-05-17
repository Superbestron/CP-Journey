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
  for (ll &i : a) {
    cin >> i;
  }
  ll lo = 0, hi = 1e13;
  auto can = [&](ll mid) {
    ll coins = k;
    for (int i = 0; i < n; i++) {
      if (a[i] < mid) coins -= (mid - a[i]);
    }
    return coins >= 0;
  };
  while (hi > lo) {
    ll mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
  ll coins = k, cnt = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] < lo) {
      coins -= (lo - a[i]);
      a[i] = lo;
    }
  }
  for (int i = 0; i < n; i++) {
    if (a[i] == lo) cnt++;
  }
  ll ans = n * lo + 1;
  ans -= cnt - coins;
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