#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, k, x;

void solve() {
  cin >> n >> k >> x;
  vi a;
  a.push_back(0);
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    a.push_back(val);
  }
  sort(a.begin() + 1, a.end(), greater<>());
  int ans = -1e9;
  for (int i = 1; i <= n; i++) a[i] += a[i - 1];
  for (int i = 0; i <= k; i++) {
    ans = max(ans, a[n] - 2 * a[min(i + x, n)] + a[i]);
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
