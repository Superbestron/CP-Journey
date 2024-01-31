#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    if (n <= 6 || n == 9) cout << "NO\n";
    else {
      if (n % 3 == 0) {
        cout << "YES\n" << 1 << ' ' << 4 << ' ' << n - 5 << '\n';
      } else {
        cout << "YES\n" << 1 << ' ' << 2 << ' ' << n - 3 << '\n';
      }
    }
  }
}