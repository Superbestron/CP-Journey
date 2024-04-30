#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;

int t, n, m;

void solve() {
  cin >> n >> m;
  vector<vi> a(n, vi(m));
  for (int i = 0; i < n; i++) {
    for (int &j : a[i]) cin >> j;
  }
  vector<vi> memo(n, vi(m));
  int gcd_val = gcd(a[0][0], a.back().back()), ans = 0;
  for (int v = sqrt(gcd_val); v; v--) {
    if (gcd_val % v) continue;
    for (int val : {v, gcd_val / v}) {
      memo[0][0] = 1;
      for (int i = 1; i < n; i++) {
        memo[i][0] = memo[i - 1][0] && a[i][0] % val == 0;
      }
      for (int i = 1; i < m; i++) {
        memo[0][i] = memo[0][i - 1] && a[0][i] % val == 0;
      }
      for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
          memo[i][j] = (memo[i][j - 1] || memo[i - 1][j]) && a[i][j] % val == 0;
        }
      }
      if (memo.back().back() == 1) {
        ans = max(ans, val);
      }
    }
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
