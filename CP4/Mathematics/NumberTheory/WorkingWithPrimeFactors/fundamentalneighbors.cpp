#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

ll fexp(ll b, ll p) {
  if (p == 0)return 1;
  if (p == 1)return b;
  if (p & 1) {
    return fexp(b, p >> 1) * fexp(b, p >> 1) * b;
  } else {
    return fexp(b, p >> 1) * fexp(b, p >> 1);
  }
}

ll primeFactors(ll N) { // pre-condition, N >= 1
  ll sum = 1;
  for (int i = 0; (i < (int) p.size()) && (p[i] * p[i] <= N); ++i) {
    if (N % p[i] == 0) {
      int power = 0;
      while (N % p[i] == 0) { // found a prime for N
        N /= p[i]; // remove it from N
        power++;
      }
      sum *= fexp(power, p[i]);
    }
  }
  return sum;
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  sieve(10000000);
  while (cin >> n) {
    cout << n << ' ' << primeFactors(n) << '\n';
  }
}