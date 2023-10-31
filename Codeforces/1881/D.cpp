#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
unordered_map<ll, int> m;

void primeFactors(ll N) { // pre-condition, N >= 1
  vll factors;
  for (int i = 0; (i < (int)p.size()) && (p[i]*p[i] <= N); ++i)
    while (N%p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      m[p[i]]++;
    }
  if (N != 1) m[N]++;
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
  int t, n, val;
  sieve(1000000);
  cin >> t;
  while (t--) {
    cin >> n;
    m.clear();
    for (int i = 0; i < n; i++) {
      cin >> val;
      primeFactors(val);
    }
    bool printed = false;
    for (auto& [num, cnt] : m) {
      if (cnt % n != 0) {
        printed = true;
        break;
      }
    }
    if (printed) cout << "NO\n";
    else cout << "YES\n";
  }
}