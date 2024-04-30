#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;

ll t, n, k, c;
const int MAX_N = 3000302;
vll mods = {3, 11, 101, 3000301};
vector<vi> fact(4, vi(MAX_N));

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

ll fexp(ll b, ll p) {
  if (p == 0) return 1;

  ll ans = fexp(b, p >> 1);
  ans = ans * ans;
  if (p & 1) ans = ans * b;
  return ans;
}

ll inv(ll a, ll p) {                                   // Fermat's little theorem
  return modPow(a, p - 2, p);                      // modPow in Section 5.8
}                                                // that runs in O(log p)

// Sped up with Lucas' Theorem
ll L_C(ll n, ll k, int idx) {
  if (n < k) return 0;
  ll MOD = mods[idx];
  if (n >= MOD) return (L_C(n % MOD, k % MOD, idx) * L_C(n / MOD, k / MOD, idx)) % MOD;
  return (((fact[idx][n] * inv(fact[idx][k], MOD)) % MOD) * inv(fact[idx][n - k], MOD)) % MOD;
}

ll crt(vll &r, vll &m) {  // m_t = m_0 * m_1 * ... * m_{n-1}
  ll mt = accumulate(m.begin(), m.end(), 1LL, multiplies<>());
  ll x = 0;
  for (int i = 0; i < m.size(); ++i) {
    ll a = mod((ll) r[i] * modInverse(mt / m[i], m[i]), m[i]);
    x = mod(x + (ll) a * (mt / m[i]), mt);
  }
  return x;
}

inline void solve() {
  cin >> n >> k >> c;
  const ll MOD = 1e10 + 3233;
  ll ans1 = L_C(n - 1, c - 1, 0);
  ll ans2 = L_C(n - 1, c - 1, 1);
  ll ans3 = L_C(n - 1, c - 1, 2);
  ll ans4 = L_C(n - 1, c - 1, 3);
  vll r = {ans1, ans2, ans3, ans4};
  cout << (2 * crt(r, mods)) % MOD << '\n';
}

// Note that 10^10 + 3233 = 3 * 11 * 101 * 3000301

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  for (int idx = 0; idx < 4; idx++) {
    fact[idx][0] = 1;
    for (int i = 1; i < MAX_N; ++i)                // O(MAX_N) pre-processing
      fact[idx][i] = ((ll) fact[idx][i - 1] * i) % mods[idx];                  // fact[i] in [0..p-1]
  }
  while (t--) {
    solve();
  }
}
