#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;

// python
//@lru_cache(maxsize=None)
//def comb(n, r):
//if r == 0 or r == n: return 1
//return comb(n - 1, r - 1) + comb(n - 1, r)
//
//
//def binomcdf(n, p, x):
//return sum([comb(n, i) * p ** i * (1 - p) ** (n - i) for i in range(x + 1)])

const int MAX_N = 100010;
const int p = 1e9 + 7;                             // p is a prime > MAX_N

vll primes;
ll fact[MAX_N], invFact[MAX_N], Fib[MAX_N], Cat[MAX_N];

ll modMultiply(ll a, ll b, ll c) {
  ll x = 0, y = a % c;
  while (b) {
    if (b & 1) x = (x + y) % c;
    y = (y * 2) % c;
    b >>= 1;
  }
  return x % c;
}

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

ll inv(ll a) {                                   // Fermat's little theorem
  return modPow(a, p - 2, p);                      // modPow in Section 5.8
}                                                // that runs in O(log p)

ll C(int n, int k, ll MOD) {                             // O(log p)
  if (n < k) return 0;                           // clearly
  return (((fact[n] * inv(fact[k])) % MOD) * inv(fact[n - k])) % MOD;
  // return (((fact[n] * invFact[k]) % MOD) * invFact[n - k]) % MOD; // O(1)
}

// Sped up with Lucas' Theorem
ll L_C(ll n, ll k, ll MOD) {
  if (n < k) return 0;
  if (n >= MOD) return (L_C(n % MOD, k % MOD) * L_C(n / MOD, k / MOD)) % MOD;
  return (((fact[n] * inv(fact[k])) % MOD) * inv(fact[n - k])) % MOD;
}

// Need to do sieve
vector<ii> prime_factorise(ll n) {
  vector<ii> prime_factors;
  for (ll i = 0; i < primes.size() && primes[i] * primes[i] <= n; i++) {
    int exp;
    if (n % primes[i] == 0) {
      exp = 0;
      while (n % primes[i] == 0) {
        n /= primes[i];
        exp++;
      }
      prime_factors.emplace_back(primes[i], exp);
    }
  }
  if (n != 1) prime_factors.emplace_back(n, 1);
  return prime_factors;
}

ll crt(vll &r, vll &m) {  // m_t = m_0 * m_1 * ... * m_{n-1}
  ll mt = accumulate(m.begin(), m.end(), 1LL, multiplies<>());
  int x = 0;
  for (int i = 0; i < m.size(); ++i) {
    int a = mod((ll) r[i] * modInverse(mt / m[i], m[i]), m[i]);
    x = mod(x + (ll) a * (mt / m[i]), mt);
  }
  return x;
}

bool verify_crt(vll &r, vll &m) {
  // Ensure r_i = r_j (mod gcd(m_i, m_j)) for all i, j
  for (int i = 0; i < (int) m.size(); ++i) {
    for (int j = i + 1; j < (int) m.size(); ++j) {
      if (mod(r[i], gcd(m[i], m[j])) != mod(r[j], gcd(m[i], m[j]))) {
        return false;
      }
    }
  }
  return true;
}

ll general_crt(vll r, vll m) {
  if (!verify_crt(r, m)) {
    return -1;
  }
  unordered_map<ll, ll> prime_highest_pow;
  unordered_map<ll, ll> S;

  for (int i = 0; i < m.size(); i++) {
    vector<ii> factors = prime_factorise(m[i]);
    for (auto &[p, exp] : factors) {
      if (prime_highest_pow[p] < exp) {
        prime_highest_pow[p] = exp;
        S[p] = r[i] % (fexp(p, exp));
      }
    }
  }

  vll nr, nm;
  for (auto &[p, exp] : prime_highest_pow) {
    nr.push_back(S[p]);
    nm.push_back(fexp(p, exp));
  }

  return crt(nr, nm);
}

int main() {
  Fib[0] = 0;                                    // the first
  Fib[1] = 1;                                    // two terms of Fibonacci
  for (int i = 2; i < MAX_N; ++i)                // O(MAX_N) pre-processing
    Fib[i] = (Fib[i - 1] + Fib[i - 2]) % p;          // Fib[i] in [0..p-1]
  cout << Fib[100000] << "\n";                   // the answer is 911435502

  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i)                // O(MAX_N) pre-processing
    fact[i] = (fact[i - 1] * i) % p;                  // fact[i] in [0..p-1]

  // invFact[MAX_N - 1] = inv(fact[MAX_N - 1]);         // one O(log p)
  // for (int i = MAX_N - 2; i >= 0; --i)             // O(MAX_N) pre-processing
  //   invFact[i] = (invFact[i + 1] * (i + 1)) % p;
  cout << C(100000, 50000) << "\n";              // the answer is 149033233

  Cat[0] = 1;
  for (int n = 0; n < MAX_N - 1; ++n)              // O(MAX_N * log p)
    Cat[n + 1] = ((4 * n + 2) % p * Cat[n] % p * inv(n + 2)) % p;
  cout << Cat[100000] << "\n";                   // the answer is 945729344

  // Fermat's little theorem, b^-1 = b^{m-2} (mod m)
  printf("%d\n", (27 % 7 * modPow(3, 5, 7)) % 7);  // example 1, output 2
  printf("%d\n", (27 % 7 * modPow(4, 5, 7)) % 7);  // example 2, output 5
  printf("%d\n",
         (520 % 18 * modPow(25, 16, 18)) % 18); // example 3, wrong answer, doesn't output 10 because 18 is not a prime

  // Using extEuclid
  printf("%d\n", (27 % 7 * modInverse(3, 7)) % 7); // example 1, output 2
  printf("%d\n", (27 % 7 * modInverse(4, 7)) % 7); // example 2, output 5
  printf("%d\n", (520 % 18 * modInverse(25, 18)) % 18); // example 3, output 10
  return 0;
}
