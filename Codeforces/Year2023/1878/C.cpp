#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  long long t, n, k, x;
  cin >> t;
  while (t--) {
    cin >> n >> k >> x;
//    cout << (n * (n + 1) / 2 - (n - k) * (n - k + 1) / 2 < x) << ' ' << (k * (k + 1) / 2 > x) << '\n';
    if ((n * (n + 1) / 2 - (n - k) * (n - k + 1) / 2 < x) || (k * (k + 1) / 2 > x)) cout << "NO\n";
    else cout << "YES\n";
  }
}