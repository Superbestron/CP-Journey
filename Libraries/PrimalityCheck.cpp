#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef unsigned long long ull;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

vll getDivisors(ll n) {
  vll ans;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      if (n / i == i) ans.push_back(i);
      else {
        ans.push_back(i);
        ans.push_back(n / i);
      }
    }
  }
  return ans;
}

vll primeFactors(ll N) { // pre-condition, N >= 1
  vll factors;
  for (int i = 0; (i < (int) p.size()) && (p[i] * p[i] <= N); ++i)
    while (N % p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      factors.push_back(p[i]);
    }
  if (N != 1) factors.push_back(N); // remaining N is a prime
  return factors;
}

void sieve(ll upperbound) { // range = [0..upperbound]
  sieve_size = upperbound + 1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = false; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i)
    if (bs[i]) {
      // cross out multiples of i starting from i*i
      for (ll j = i * i; j < sieve_size; j += i) bs[j] = false;
      p.push_back(i); // add prime i to the list
    }
}

bool isPrime(ll N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
}

unordered_map<ll, int> primeFactors2(ll N) { // pre-condition, N >= 1
  unordered_map<ll, int> factors;
  if (N == 1) return factors;
  if (isPrime(N)) { factors[N] = 1; return factors; }
  vll prime_facs = primeFactors(N);
  for (ll& x : prime_facs) ++factors[x];
  return factors;
}

int numPF(ll N) {
  int ans = 0;
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    while (N % p[i] == 0) {
      N /= p[i];
      ++ans;
    }
  return ans + (N != 1);
}

int numDiffPF(ll N) {
  int ans = 0;
  for (int i = 0; i < p.size() && p[i] * p[i] <= N; ++i) {
    if (N % p[i] == 0) ++ans;                      // count this prime factor
    while (N % p[i] == 0) N /= p[i];               // only once
  }
  if (N != 1) ++ans;
  return ans;
}

ll sumPF(ll N) {
  ll ans = 0;
  for (int i = 0; i < p.size() && p[i] * p[i] <= N; ++i)
    while (N % p[i] == 0) {
      N /= p[i];
      ans += p[i];
    }
  if (N != 1) ans += N;
  return ans;
}

int numDiv(ll N) {
  int ans = 1;                                   // start from ans = 1
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i) {
    int power = 0;                               // count the power
    while (N % p[i] == 0) {
      N /= p[i];
      ++power;
    }
    ans *= power + 1;                              // follow the formula
  }
  return (N != 1) ? 2 * ans : ans;                 // last factor = N^1
}

ll sumDiv(ll N) {
  ll ans = 1;                                    // start from ans = 1
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i) {
    ll multiplier = p[i], total = 1;
    while (N % p[i] == 0) {
      N /= p[i];
      total += multiplier;
      multiplier *= p[i];
    }                                            // total for
    ans *= total;                                // this prime factor
  }
  if (N != 1) ans *= (N + 1);                      // N^2-1/N-1 = N+1
  return ans;
}

ll EulerPhi(ll N) {
  ll ans = N;                                    // start from ans = N
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i) {
    if (N % p[i] == 0) ans -= ans / p[i];            // count unique
    while (N % p[i] == 0) N /= p[i];               // prime factor
  }
  if (N != 1) ans -= ans / N;                      // last factor
  return ans;
}

int factorSum(ll N) {       // pre-condition, N >= 1
  int s = 0;
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    while (N % p[i] == 0) {                        // found a prime for N
      s += p[i];
      N /= p[i];                                 // remove it from N
    }
  if (N != 1) s += N;                            // remaining N is a prime
  return s;
}

deque<ll> all_divisors(ll N) {
  ll sq = sqrt(N);
  deque<ll> divs;
  for (int i = sq; i >= 1; --i) {
    if (N % i == 0) {
      divs.push_front(i);
      if (N / i != i) divs.push_back(N / i);
    }
  }
  return divs;
}

/*** Miller Rabin Primality Test ***/

// modular multiplication to numbers up to 10^18 in O(1)
// __int128 is a well accepted gcc extension also compatible with clang
inline ull mul(ull a, ull b, ull c) { return __int128(a) * b % c; }

// modular exponatiation in O(log(n))
inline ull power(ull a, ull b, ull c) {
  ull res = 1;
  while (b > 0) {
    if (b & 1) res = mul(res, a, c);
    a = mul(a, a, c);
    b /= 2;
  }
  return res;
}

// miller-rabin strong pseudoprimality test in complexity O(log(n))
// returns false if n is composite
// returns true if n is prime or strong pseudoprime in base a
bool witness(ull n, ull d, ull s, ull a) {
  ull x = power(a, d, n), y;

  // pass through all a^(d*2^k) mod n ( 0 <= k <= s )
  while (s--) {
    y = mul(x, x, n);
    // if y is equal to 1 it must have been a square of -1 or 1 mod n to be prime
    // if not the number is composite
    if (y == 1 and x != 1 and x != n - 1) return false;
    x = y;
  }
  // if a^(d*2^s) != 1 mod n than n is not prime
  // a^(n-1) = 1 mod n for every n prime (fermats little theorem)
  if (y != 1) return false;
  // if the number is not confirmed composite return that it is either a prime
  // or strong pseudoprime in base a
  return true;
}

// all numbers up to 10^18 are confirmed composite if these bases are used
// if numbers are up to 10^9 use primes_small to confirm compositeness
ull primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
ull primes_small[] = {2, 3, 5, 7, 11};

// ckeck primality up to 10^18 in O(log(n)*k)
// to numbers up to 10^18, testing all 9 prime numbers smaller or equal to 23 suffices
bool is_prime_miller_rabin(ull n) {
  // trivial cases
  if (n == 2 or n == 3) return true;
  if (n < 2 or n % 2 == 0 or n % 3 == 0) return false;

  // calculate d = biggest odd number divisor of n-1
  // s = number of the biggest power of two that divides n-1
  // such that n-1 = d*2^s (d odd)
  // __builtin_ctzll returns expoent of biggest power of two that divides n-1
  ull s = __builtin_ctzll(n - 1);
  ull d = (n - 1) >> s;

  // check primality with the 13 bases
  for (ull p : primes) {
    if (p == n) return true;
    if (!witness(n, d, s, p)) return false;  // if composite returns false
  }
  // after the iterations all remaining numbers are prime
  return true;
}

ull random_ull(ull l, ull r) {
  static random_device rd;
  static mt19937_64 gen(rd());
  return uniform_int_distribution<ull>(l, r)(gen);
}

bool is_prime_miller_rabin_2(ull n) {
  int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
                        37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
                        79, 83, 89, 97, 101, 103, 107, 109, 113,
                        127, 131, 137, 139, 149, 151, 157, 163,
                        167, 173, 179, 181, 191, 193, 197, 199,
                        211, 223, 227, 229, 233, 239, 241, 251};
  for (int p : small_primes) {
    if (n == p) return true;
    if (n % p == 0) return false;
  }
  ull d = n - 1, s = 0;
  while (d % 2 == 0) {
    d /= 2;
    ++s;
  }
  ull x = power(random_ull(2, n - 2), d, n);
  if (x == 1 || x == n - 1) return true;
  for (int r = 0; r < s; ++r) {
    x = mul(x, x, n);
    if (x == 1) return false;
    if (x == n - 1) return true;
  }
  return false;
}

/*** Pollard's Rho Algorithm ***/

int bit_length(ll N) { return 64 - __builtin_clzll(N); }

ll f(ll x, ll b, ll n) { return (mul(x, x, n) + b) % n; }

ll rho(ll N) {
  if (N % 2 == 0) return 2;
  int n_bit_length = bit_length(N);
  ll mask = (1LL << n_bit_length) - 1;
  ll b = rand() & mask;
  ll x = rand() & mask;
  ll y = x, d;
  while (true) {
    x = f(x, b, N);
    y = f(f(y, b, N), b, N);
    d = gcd(abs(x - y), N);
    if (d != 1) return d;
  }
}

void pollard_rho(ll N, vll &vec) {
  if (N == 1LL) return;
  if (isPrime(N)) {
    vec.push_back(N);
    return;
  }
  ll d = rho(N);
  pollard_rho(d, vec);
  pollard_rho(N / d, vec);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000000);
  for (int i = 1; i <= 10; i++) {
    cout << is_prime_miller_rabin(i) << '\n';
  }
}
