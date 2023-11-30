#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e4;

ll mod(ll a, int m) {                          // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll modPow(ll b, ll p, int m) {                // assume 0 <= b < m
  if (p == 0) return 1;
  ll ans = modPow(b, p / 2, m);                   // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  ll x, y;
  char op;
  while (getline(cin, s)) {
    istringstream str(s);
    str >> x >> op >> y;
    if (op == '+') {
      cout << (x + y) % MOD << '\n';
    } else if (op == '*') {
      cout << ((x % MOD) * (y % MOD)) % MOD << '\n';
    } else {
      cout << modPow(x, y, MOD) << '\n';
    }
  }
}
