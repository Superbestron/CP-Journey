#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vll;

int sieve_size;
bitset<10000010> bs;
vll p; // compact list of primes

void sieve(int upperbound) { // range = [0..upperbound]
  sieve_size = upperbound + 1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = 0; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i) if (bs[i]) {
// cross out multiples of i starting from i*i
      if (bs[i] == 0) continue;
      for (ll j = i; j < sieve_size; j += i) {
        if (bs[j] == 0) continue;
        bs[j] = 0;
      }
      p.push_back(i); // add prime i to the list
    }
}

vll primeFactors(ll N) { // pre-condition, N >= 1
  vll factors;
  for (int i = 0; (i < (int)p.size()) && (p[i]*p[i] <= N); ++i)
    while (N%p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      factors.push_back(p[i]);
    }
  if (N != 1) factors.push_back(N); // remaining N is a prime
  return factors;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000000);
  int N;
  while (cin >> N && N != 4) {
    vll v(primeFactors(N));
    int ans = 1;
    while (v.size() > 1) {
      N = accumulate(v.begin(), v.end(), 0);
      v = primeFactors(N);
      ans++;
    }
    cout << N << ' ' << ans << '\n';
  }
}