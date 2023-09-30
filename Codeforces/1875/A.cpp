#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, a, b, n, v;
  cin >> t;
  while (t--) {
    cin >> a >> b >> n;
    long long ans = b;
    for (int i = 0; i < n; i++) {
      cin >> v;
      ans += min(a - 1, v);
    }
    cout << ans << '\n';
  }
}