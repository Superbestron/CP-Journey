#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<ll, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

int t, n;

void solve() {
  cin >> n;
  vi a(2 * n), inc, dec;
  int ans = 1e9;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }
  inc.push_back(0);
  dec.push_back(0);
  for (int i = 0; i < 2 * n - 1; i++) {
    inc.push_back(a[i] <= a[i + 1] ? inc.back() + 1 : 0);
    dec.push_back(a[i] >= a[i + 1] ? dec.back() + 1 : 0);
  }
  for (int i = n - 1; i < 2 * n; i++) {
    if (inc[i] >= n - 1) ans = min(ans, min(2 * n - 1 - i, i - (n - 1) + 2));
    if (dec[i] >= n - 1) ans = min(ans, min(2 * n - 1 - i + 1, i - (n - 1) + 1));
  }
  if (ans == 1e9) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
