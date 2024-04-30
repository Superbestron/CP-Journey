#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod(ll a, ll m) {                            // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll modPow(ll b, ll p, ll m) {                  // assume 0 <= b < m
  if (p == 0) return 1;
  ll ans = modPow(b, p / 2, m);                    // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int a, b;
  cin >> a >> b;
  if (a & 1) cout << 0 << '\n';
  else cout << modPow(a / 2, b, a) << '\n';
}
