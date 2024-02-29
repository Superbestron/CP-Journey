#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;

void solve() {
  cin >> n;
  vector<int> a(n);
  ll prev;
  ll ans = -1e9, sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (i != 0 && ((prev & 1) == (a[i] & 1))) {
      sum = a[i];
    } else {
      sum += a[i];
    }
    ans = max(ans, sum);
    if (sum < 0) sum = 0;
    prev = a[i];
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
