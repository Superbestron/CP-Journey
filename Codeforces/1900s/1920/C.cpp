#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  int ans = 0;
  for (int k = 1; k <= n; k++) {
    if (n % k == 0) {
      int num = 0;
      for (int i = 0; i + k < n; i++) {
        num = gcd(num, abs(a[i + k] - a[i]));
      }
      ans += (num != 1);
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
