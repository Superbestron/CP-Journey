#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, val;

void solve() {
  cin >> n;
  vector<int> a(n);
  int min_idx, curr = INT32_MAX, ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] < curr) {
      curr = a[i];
      min_idx = i;
    }
  }
  int prev = a[min_idx];
  for (int j = min_idx + 1; j < n; j++) {
    if (a[j] < prev) {
      cout << -1 << '\n';
      return;
    }
    prev = a[j];
  }
  cout << min_idx << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}