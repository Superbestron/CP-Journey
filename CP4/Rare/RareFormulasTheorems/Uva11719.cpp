#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = (ll) 1e16 + 7;                             // p is a prime > MAX_N

ll modmultiply(ll a, ll b, ll c) {
  ll x = 0, y = a % c;
  while (b) {
    if (b & 1) x = (x + y) % c;
    y = (y * 2) % c;
    b >>= 1;
  }
  return x % c;
}

ll modPow(ll x, ll y, ll mod) {
  ll ret = 1;// ret = x^y%mod;
  while (y) {
    if (y & 1)
      //ret = (ret*x)%mod;
      ret = modmultiply(ret, x, mod);
    //x = (x*x)%mod;
    x = modmultiply(x, x, mod);
    y >>= 1;
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll T, R, C;
  cin >> T;
  while (T--) {
    cin >> R >> C;
    ll M = R * C / 2, N = R * C - M;
    cout << modmultiply(modPow(M, N - 1, MOD), modPow(N, M - 1, MOD), MOD) << '\n';
  }
}
