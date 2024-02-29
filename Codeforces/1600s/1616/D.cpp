#include <bits/stdc++.h>
using namespace std;

int t, n, x;

inline int solve() {
  cin >> n;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  cin >> x;

  int ans = 0;
  for (int i = 0, j = 0; i < n; i++) {
    bool nice = true;
    if (i - j >= 1 && a[i - 1] + a[i] < 2 * x) {
      nice = false;
    }
    if (i - j >= 2 && a[i - 2] + a[i - 1] + a[i] < 3 * x) {
      nice = false;
    }
    if (!nice) {
      ans++;
      j = i + 1;
    }
  }

  return n - ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}
