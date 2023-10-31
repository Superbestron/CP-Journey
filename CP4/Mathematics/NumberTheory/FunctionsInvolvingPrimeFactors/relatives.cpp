#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

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

ll EulerPhi(ll N) {
  ll ans = N;                                    // start from ans = N
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i) {
    if (N % p[i] == 0) ans -= ans / p[i];            // count unique
    while (N % p[i] == 0) N /= p[i];               // prime factor
  }
  if (N != 1) ans -= ans / N;                      // last factor
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  sieve(1000000);
  while (cin >> n && n != 0) {
    cout << EulerPhi(n) << '\n';
  }
}