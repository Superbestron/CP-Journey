#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

vector<tuple<ll, ll>> primeFactors(int N) { // pre-condition, N >= 1
  vector<tuple<ll, ll>> factors;
  for (int i = 0; (i < (int)p.size()) && (p[i]*p[i] <= N); ++i) {
    if (N % p[i]) continue;
    int exp = 0;
    while (N % p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      exp++;
    }
    factors.emplace_back(p[i], exp);
  }
  if (N != 1) {
    factors.emplace_back(N, 1); // remaining N is a prime
  }
  return factors;
}

void sieve(ll upperbound) { // range = [0..upperbound]
  sieve_size = upperbound+1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = false; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i) if (bs[i]) {
// cross out multiples of i starting from i*i
      for (ll j = i*i; j < sieve_size; j += i) bs[j] = false;
      p.push_back(i); // add prime i to the list
    }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  sieve(10000000);
  while (scanf("%lld", &N) != EOF) {
    if (N < -1) {
      cout << -1 << ' ';
    }
    N = abs(N);
    auto factors = primeFactors(N);
    for (auto& [num, cnt] : factors) {
      cout << num;
      if (cnt > 1) cout << '^' << cnt;
      cout << ' ';
    }
    cout << '\n';
  }
}