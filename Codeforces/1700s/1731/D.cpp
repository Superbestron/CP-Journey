#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, m;

void solve() {
  cin >> n >> m;
  vector<vi> a(n, vi(m));
  for (auto &row : a) {
    for (int &i : row) cin >> i;
  }
  int lo = 1, hi = min(n, m);
  while (hi > lo) {
    int mid = lo + (hi - lo + 1) / 2;
    vector<vi> memo(n + 1, vi(m + 1));
    int mx = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (a[i - 1][j - 1] >= mid) {
          memo[i][j] = min(memo[i - 1][j - 1], min(memo[i][j - 1], memo[i - 1][j])) + 1;
          mx = max(mx, memo[i][j]);
        }
      }
    }
    (mx >= mid) ? lo = mid : hi = mid - 1;
  }
  cout << lo << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
