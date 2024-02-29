#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, x;

void solve() {
  cin >> n >> x;
  vector<int> v(n);
  for (int &i : v) cin >> i;
  int ans = 0;
  for (int i = 0; i < n - 1; i++) {
    ans = max(ans, v[i + 1] - v[i]);
  }
  ans = max(ans, 2 * (x - v[n - 1]));
  ans = max(ans, v[0]);
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
