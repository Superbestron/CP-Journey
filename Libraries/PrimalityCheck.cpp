#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef unsigned long long ull;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

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

bool isPrime(ll N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
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

unordered_map<ll, int> primeFactors2(ll N) { // pre-condition, N >= 1
  unordered_map<ll, int> factors;
  if (N == 1) return factors;
  if (isPrime(N)) {
    factors[N] = 1;
    return factors;
  }
  vll prime_facs = primeFactors(N);
  for (ll &x : prime_facs) ++factors[x];
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

ll EulerPhi(ll N) {
  ll ans = N;                                    // start from ans = N
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i) {
    if (N % p[i] == 0) ans -= ans / p[i];            // count unique
    while (N % p[i] == 0) N /= p[i];               // prime factor
  }
  if (N != 1) ans -= ans / N;                      // last factor
  return ans;
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

const int MAX_N = 10000000;
vll numDiffPFarr(MAX_N + 10);
void numDiffPFMany() {
  for (int i = 2; i <= MAX_N; i++)
    if (numDiffPFarr[i] == 0)  // i is a prime number, remove this line if counting divisors
      for (int j = i; j <= MAX_N; j += i)
        numDiffPFarr[j]++;
}

vll EulerPhiArr(MAX_N + 10);
void EulerPhiMany() {
  for (int i = 1; i <= MAX_N; i++) EulerPhiArr[i] = i;
  for (int i = 2; i <= MAX_N; i++)
    if (EulerPhiArr[i] == i)  // i is a prime number
      for (int j = i; j <= MAX_N; j += i)
        EulerPhiArr[j] = (EulerPhiArr[j] / i) * (i - 1);
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

ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll) M);
}

ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n - 1), d = n >> s;
  for (ull a : A) {   // ^ count trailing zeroes
    ull p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n - 1 && i != s) return false;
  }
  return true;
}

// ONLY FOR <= 1e12
struct _count_primes_struct_t_ {
  vi primes;
  vi mnprimes;
  ll ans;
  ll y;
  vector<pair<pair<ll, int>, char>> queries;

  ll count_primes(ll n) {
    // this y is actually n/y
    // also no logarithms, welcome to reality, this y is the best for n=10^12 or n=10^13
    y = pow(n, 0.64);
    if (n < 100) y = n;

    // linear sieve
    primes.clear();
    mnprimes.assign(y + 1, -1);
    ans = 0;
    for (int i = 2; i <= y; ++i) {
      if (mnprimes[i] == -1) {
        mnprimes[i] = primes.size();
        primes.push_back(i);
      }
      for (int k = 0; k < primes.size(); ++k) {
        int j = primes[k];
        if (i * j > y) break;
        mnprimes[i * j] = k;
        if (i % j == 0) break;
      }
    }
    if (n < 100) return primes.size();
    ll s = n / y;

    for (int p : primes) {
      if (p > s) break;
      ans++;
    }
    // pi(n / y)
    int ssz = ans;

    // F with two pointers
    int ptr = primes.size() - 1;
    for (int i = ssz; i < primes.size(); ++i) {
      while (ptr >= i && (ll) primes[i] * primes[ptr] > n)
        --ptr;
      if (ptr < i) break;
      ans -= ptr - i + 1;
    }

    // phi, store all queries
    phi(n, ssz - 1);

    sort(queries.begin(), queries.end());
    int ind = 2;
    int sz = primes.size();

    // the order in fenwick will be reversed, because prefix sum in a fenwick is just one query
    fenwick fw(sz);
    for (auto [na, sign] : queries) {
      auto [n, a] = na;
      while (ind <= n)
        fw.add(sz - 1 - mnprimes[ind++], 1);
      ans += (fw.ask(sz - a - 2) + 1) * sign;
    }
    queries.clear();
    return ans - 1;
  }

  void phi(ll n, int a, int sign = 1) {
    if (n == 0) return;
    if (a == -1) {
      ans += n * sign;
      return;
    }
    if (n <= y) {
      queries.emplace_back(make_pair(n, a), sign);
      return;
    }
    phi(n, a - 1, sign);
    phi(n / primes[a], a - 1, -sign);
  }

  struct fenwick {
    vi tree;
    int n;

    fenwick(int n = 0) : n(n) {
      tree.assign(n, 0);
    }

    void add(int i, int k) {
      for (; i < n; i = (i | (i + 1)))
        tree[i] += k;
    }

    int ask(int r) {
      int res = 0;
      for (; r >= 0; r = (r & (r + 1)) - 1)
        res += tree[r];
      return res;
    }
  };
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  sieve(10000000);
  ll res = _count_primes_struct_t_().count_primes(n);
  cout << res << '\n';
}
