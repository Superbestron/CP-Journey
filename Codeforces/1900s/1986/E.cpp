#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

inline void solve() {
  cin >> n >> k;
  vi v(n);
  int p = 0;
  map<int, int> c;
  map<int, vi> AL;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    int x = v[i] % k;
    c[x]++;
    AL[x].push_back(v[i]);
  }
  for (auto &[i, cnt] : c) {
    if (cnt % 2 != 0) p++;
  }
  if (((n % 2 != 0) && p > 1) || (!(n % 2 != 0) && p > 0)) cout << -1 << '\n';
  else {
    ll ans = 0;
    for (auto &[i, cnt] : c) {
      vi &ar = AL[i];
      sort(ar.begin(), ar.end());
      ll lo = 0;
      for (int j = 0; j < ar.size() - 1; j += 2) {
        lo += ar[j + 1] - ar[j];
      }
      if (cnt % 2 != 0) {
        ll curr = lo;
        for (int k = ar.size() - 1; k > 1; k -= 2) {
          curr += ar[k] - ar[k - 1] * 2 + ar[k - 2];
          lo = min(lo, curr);
        }
      }
      ans += lo / k;
    }
    cout << ans << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
}
