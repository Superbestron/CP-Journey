#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

inline void solve() {
  cin >> n >> m;
  vector<vi> A(n, vi(m));
  for (auto &row : A) {
    for (int &i : row) cin >> i;
  }
  while (true) {
    bool changed = false;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int mx = 0;
        if (i != 0) mx = max(mx, A[i - 1][j]);
        if (i != n - 1) mx = max(mx, A[i + 1][j]);
        if (j != 0) mx = max(mx, A[i][j - 1]);
        if (j != m - 1) mx = max(mx, A[i][j + 1]);
        if (mx < A[i][j]) {
          A[i][j] = mx;
          changed = true;
        }
      }
    }
    if (!changed) break;
  }
  done:
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << A[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
