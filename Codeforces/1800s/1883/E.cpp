#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
typedef long double ld;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<ld> v(n);
    for (ld &i : v) {
      cin >> i;
      i = log2(i);
    }
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
      if (v[i + 1] >= v[i]) continue;
      ans += ceill(v[i] - v[i + 1] - EPS);
      v[i + 1] += ceill(v[i] - v[i + 1] - EPS);
    }
    cout << ans << '\n';
  }
}