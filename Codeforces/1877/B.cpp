#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n, p;
  cin >> t;
  while (t--) {
    cin >> n >> p;
    vector<pair<ll, ll>> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].second;
    for (int i = 0; i < n; i++) cin >> v[i].first;
    ll ans = p;
    n--;
    int idx = 0;
    sort(v.begin(), v.end());
    while (n) {
      auto &pr = v[idx++];
      ans += min(pr.first, p) * min(n, pr.second);
      n -= min(n, pr.second);
    }

    cout << ans << '\n';
  }
}
