#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t, n;

void solve() {
  cin >> n;
  vector<ll> v(n);
  ll ans = 0, prev = 0;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    ans += max(0LL, v[i] - prev);
    prev = v[i];
  }
  cout << ans - 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
