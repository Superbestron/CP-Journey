#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  vector<vii> pref(32, vii(n + 1)), suff(32, vii(n + 1));
  for (int j = 0; j < 32; j++) {
    int mask = 1 << j;
    for (int i = 1; i <= n; i++) {
      int bit = mask & a[i];
      // first is odd, second is even
      if (bit) {
        pref[j][i].first = 1 + pref[j][i - 1].second; // newly encountered 1 also considered
        pref[j][i].second = pref[j][i - 1].first;
      } else {
        pref[j][i].second = 1 + pref[j][i - 1].second; // newly encountered 0 also considered
        pref[j][i].first = pref[j][i - 1].first;
      }
    }
    for (int i = n; i; i--) {
      int bit = mask & a[i];
      if (bit) {
        suff[j][i - 1].second = suff[j][i].first;
        suff[j][i - 1].first = 1 + suff[j][i].second; // newly encountered 1 also considered
      } else {
        suff[j][i - 1].first = suff[j][i].first;
        suff[j][i - 1].second = 1 + suff[j][i].second; // newly encountered 0 also considered
      }
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    int bit = 31 - __builtin_clz(a[i]);
    ans += (ll) pref[bit][i - 1].first * (suff[bit][i].second + 1);
    ans += (ll) (pref[bit][i - 1].second + 1) * suff[bit][i].first;
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
