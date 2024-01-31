#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m, k;
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    int te;
    if (m >= n) te = (n - 1 + m / n);
    else te = m;
    if (k > 3) cout << 0 << '\n';
    else if (k == 1) {
      cout << 1 << '\n';
    } else if (k == 2) {
      cout << te << '\n';
    } else if (k == 3) {
      cout << m - te << '\n';
    }
  }
}