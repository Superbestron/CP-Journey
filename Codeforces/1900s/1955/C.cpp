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
  vll a(n), pref(n + 1), suff(n + 1);
  ll sum = 0;
  for (ll &i : a) {
    cin >> i;
    sum += i;
  }
  if (sum <= k) {
    cout << n << '\n';
    return;
  }
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + a[i];
  }
  for (int i = n - 1; i >= 0; i--) {
    suff[i] = suff[i + 1] + a[i];
  }
  sort(suff.begin(), suff.end());
  int idx = upper_bound(pref.begin(), pref.end(), (k + 1) / 2) - pref.begin();
  idx--;
  ll ans = idx;
  int idx2 = upper_bound(suff.begin(), suff.end(), k / 2) - suff.begin();
  idx2--;
  ans += idx2;
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
