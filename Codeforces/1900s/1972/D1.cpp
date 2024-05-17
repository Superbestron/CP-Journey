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
  ll ans = n;
  for (ll i = 2; i <= m; i++) {
    ll sqr = i * i;
    ll base = sqr - i;
    ll rem = n - base;
    if (rem < 0) break;
    ans += 1LL + rem / sqr;
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
