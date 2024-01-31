#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

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

// sieve(10000000);
// primeFactors(N);
