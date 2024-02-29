#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n; cin >> t;
  while (t--) {
    cin >> n;
    ll sum2n = n * (2 + (2 * n - 1)), sumn = n * (2 + (n - 1)) / 2;
    if ((sum2n - sumn) % n == 0) {
      cout << "Yes\n";
      for (int i = 1; i <= (n + 1) / 2; i++) {
        cout << n + i << ' ' << n / 2 + i << '\n';
      }
      for (int i = 1; i < (n + 1) / 2; i++) {
        cout << i << ' ' << n + n / 2 + i + 1 << '\n';
      }
    } else cout << "No\n";
  }
}
