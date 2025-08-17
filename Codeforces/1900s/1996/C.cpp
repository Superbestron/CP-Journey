#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int t, n, q;
string as, bs;

inline void solve() {
  cin >> n >> q;
  vector<vi> a(n + 1, vi(26)), b(n + 1, vi(26));
  cin >> as >> bs;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 26; j++) a[i][j] = a[i - 1][j], b[i][j] = b[i - 1][j];
    if (as[i - 1] != bs[i - 1]) {
      a[i][as[i - 1] - 'a']++;
      b[i][bs[i - 1] - 'a']++;
    }
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    int out = 0;
    for (int j = 0; j < 26; j++) {
      int distA = a[r][j] - a[l - 1][j];
      int distB = b[r][j] - b[l - 1][j];
      out += abs(distA - distB);
    }
    cout << out / 2 << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
