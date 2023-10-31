#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

ll sumDiv(ll N) { // pre-condition, N >= 1
  ll ans = 1;
  for (int i = 0; (i < (int) p.size()) && (p[i] * p[i] <= N); ++i) {
    ll multiplier = p[i], total = 1;
    while (N % p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      total += multiplier;
      multiplier *= p[i];
    }
    ans *= total;
  }
  if (N != 1) ans *= N + 1;
  return ans;
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  sieve(10000000);
  while (cin >> n) {
    ll ans = sumDiv(n) - n;
    cout << n;
    if (ans == n) cout << " perfect\n";
    else if (abs(ans - n) <= 2) cout << " almost perfect\n";
    else cout << " not perfect\n";
  }
}