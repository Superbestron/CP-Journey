#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod(ll a, ll m) {                          // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll extEuclid(ll a, ll b, ll &x, ll &y) {    // pass x and y by ref
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {                                    // repeats until b == 0
    ll q = a / b;
    tie(a, b) = tuple(b, a % b);
    tie(x, xx) = tuple(xx, x - q * xx);
    tie(y, yy) = tuple(yy, y - q * yy);
  }
  return a;                                      // returns gcd(a, b)
}

ll modInverse(ll b, ll m) {                   // returns b^(-1) (mod m)
  ll x, y;
  ll d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return mod(x, m);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, t, x, y;
  char op;
  while (cin >> n >> t && !(n == 0 && t == 0)) {
    while (t--) {
      cin >> x >> op >> y;
      if (op == '+') cout << (x + y) % n << '\n';
      else if (op == '-') cout << (x - y + n) % n << '\n';
      else if (op == '*') cout << ((x % n) * (y % n)) % n << '\n';
      else {
        ll ans = modInverse(y, n);
        if (ans < 0) cout << -1 << '\n';
        else cout << mod(x * ans, n) << '\n';
      }
    }
  }
}