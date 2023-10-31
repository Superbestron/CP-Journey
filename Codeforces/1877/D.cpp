#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, a[100010], ans;
ll mod = 998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  vector<pair<ll, ll>> v;
  for (int i = 1; i <= n; i++) {
    ll mx = 0;
    for (int j = i; j <= n; j += i) mx = max(mx, a[j]);
    v.emplace_back( mx, i );
  }
  sort(v.begin(), v.end());
  ll w = 1;
  for (int i = 0; i < n; i++) {
    ans = (ans + w * v[i].first) % mod;
    w = w * 2 % mod;
  }
  cout << ans;
}