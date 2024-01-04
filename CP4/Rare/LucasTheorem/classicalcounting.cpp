#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;

const int MAX_N = 100010;
ll fact[MAX_N][2], invFact[MAX_N][2];
vll MODS = {29, 34483};  // 29 * 34483 = 1e6 + 7 (both prime factors are square-free)

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

ll inv(ll a, ll p) {                                   // Fermat's little theorem
  return modPow(a, p - 2, p);                      // modPow in Section 5.8
}                                                // that runs in O(log p)

ll C(ll n, ll k, int idx) {
  if (n < k) return 0;
  if (n >= MODS[idx]) return (C(n % MODS[idx], k % MODS[idx], idx) * C(n / MODS[idx], k / MODS[idx], idx)) % MODS[idx];
  return (((fact[n][idx] * inv(fact[k][idx], MODS[idx])) % MODS[idx]) * inv(fact[n - k][idx], MODS[idx])) % MODS[idx];
}

ll extEuclid(ll a, ll b, ll &x, ll &y) {    // pass x and y by ref
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {                                    // repeats until b == 0
    int q = a / b;
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

ll crt(vll &r, vll &m) {  // m_t = m_0 * m_1 * ... * m_{n-1}
  ll mt = accumulate(m.begin(), m.end(), 1, multiplies<>());
  ll x = 0;
  for (int i = 0; i < m.size(); ++i) {
    ll a = mod(r[i] * modInverse(mt / m[i], m[i]), m[i]);
    x = mod(x + a * (mt / m[i]), mt);
  }
  return x;
}

// Main tricky part is that Modulus given is not a prime, hence we need to use CRT (with Lucas Theorem) to solve.
// i.e. cannot simply compute directly using Mod Inverse

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, K;
  cin >> N >> M >> K;
  for (int idx = 0; idx < 2; idx++) {
    fact[0][idx] = 1;
    for (int i = 1; i < MAX_N; ++i)                // O(MAX_N) pre-processing
      fact[i][idx] = (fact[i - 1][idx] * i) % MODS[idx];                  // fact[i] in [0..p-1]
    invFact[MAX_N - 1][idx] = inv(fact[MAX_N - 1][idx], MODS[idx]);         // one O(log p)
    for (int i = MAX_N - 2; i >= 0; --i)             // O(MAX_N) pre-processing
      invFact[i][idx] = (invFact[i + 1][idx] * (i + 1)) % MODS[idx];
  }

  vll r;
  for (int j = 0; j < 2; j++) {
    ll ans = 0;
    for (int i = 0; (i <= N) && (K >= i * (M + 1)); i++) {
      ans += (i & 1 ? -1 : 1) * C(N, i, j) * C(N + K - 1 - i * (M + 1), N - 1, j);
      ans %= MODS[j];
    }
    r.emplace_back(ans);
  }
  cout << crt(r, MODS) << '\n';
}
