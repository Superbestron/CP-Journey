#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, l, k, q;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> v(n + 1, vector<int>(30)); // holes or zeroes
    for (int& i : a) cin >> i;
    cin >> q;
    for (int i = 29; i >= 0; i--) {
      int mask = (1 << i);
      for (int j = 0; j < n; j++) {
        if (mask & a[j]) {
          v[j + 1][i] = v[j][i] + 1;
        } else {
          v[j + 1][i] = v[j][i];
        }
      }
    }
    for (int i = 0; i < q; i++) {
      cin >> l >> k;
      // biggest number you can possibly get
      if (a[l - 1] < k) {
        cout << -1 << ' ';
        continue;
      }
      int lo = l, hi = n;
      while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        int num = 0;
        for (int j = 0; j < 30; j++) {
          if (v[mid][j] - v[l - 1][j] == mid - l + 1) {
            num += (1 << j);
          }
        }
        if (num >= k) lo = mid;
        else hi = mid - 1;
      }
      cout << lo << ' ';
    }
    cout << '\n';
  }
}