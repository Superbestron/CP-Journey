#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;

inline void solve() {
  cin >> n;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  vector<ll> maxi, mini;
  vector<pair<int, ll>> curr;
  vector<int> factors;
  for (int i = 1; i <= n; i++) {
    if (n % i == 0 && i != n) factors.push_back(i), maxi.push_back(0), mini.push_back(1e18);
    curr.emplace_back(0, 0);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < factors.size(); j++) {
      curr[j].second += a[i];
      curr[j].first++;
      if (curr[j].first == factors[j]) {
        maxi[j] = max(maxi[j], curr[j].second);
        mini[j] = min(mini[j], curr[j].second);
        curr[j].first = 0, curr[j].second = 0;
      }
    }
  }
  ll ans = 0;
  for (int i = 0; i < maxi.size(); i++) {
    ans = max(ans, maxi[i] - mini[i]);
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