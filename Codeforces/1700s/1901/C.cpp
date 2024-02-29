#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t, n;

void solve() {
  cin >> n;
  vector<ll> v(n), output;
  ll mini = 1e10, maxi = -1;
  for (ll &i : v) {
    cin >> i;
    mini = min(mini, i);
    maxi = max(maxi, i);
  }
  ll ans = 0, diff = maxi - mini;
  while (diff != 0) {
    diff <<= 1;
    ans++;
  }
  cout << ans << '\n';
  if (ans <= n) {
    for (int i = 0; i < ans; i++) cout << mini << ' ';
    if (ans != 0) cout << '\n';
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
