#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int mod(int a, int m) {                          // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

int extEuclid(int a, int b, int &x, int &y) {    // pass x and y by ref
  int xx = y = 0;
  int yy = x = 1;
  while (b) {                                    // repeats until b == 0
    int q = a / b;
    tie(a, b) = tuple(b, a % b);
    tie(x, xx) = tuple(xx, x - q * xx);
    tie(y, yy) = tuple(yy, y - q * yy);
  }
  return a;                                      // returns gcd(a, b)
}

int modInverse(int b, int m) {                   // returns b^(-1) (mod m)
  int x, y;
  int d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return mod(x, m);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, K, C;
  cin >> t;
  while (t--) {
    cin >> K >> C;
    int ans = modInverse(C, K);
    if (C == 1) {
      if (C == 1e9) cout << "IMPOSSIBLE\n";
      else cout << K + 1 << '\n';
    } else if (K == 1) {
      cout << 1 << '\n';
    } else if (ans == -1) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n';
  }
}