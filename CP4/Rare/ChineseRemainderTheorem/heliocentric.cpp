#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int mod(ll a, int m) {                           // returns a (mod m)
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

int crt(vi r, vi m) {
  int mt = accumulate(m.begin(), m.end(), 1, multiplies<>());
  int x = 0;
  for (int i = 0; i < (int) m.size(); ++i) {
    int a = mod((ll) r[i] * modInverse(mt / m[i], m[i]), m[i]);
    x = mod(x + (ll) a * (mt / m[i]), mt);
  }
  return x;
}

int main() {
  int e, m, caseNo = 1;
  while (cin >> e >> m) {
    vi orbit({365, 687});
    vi r({365 - e, 687 - m});
    int ans = crt(r, orbit);
    cout << "Case " << caseNo++ << ": " << ans << '\n';
  }
}
