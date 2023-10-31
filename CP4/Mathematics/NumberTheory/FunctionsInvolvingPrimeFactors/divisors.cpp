#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<1000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
unordered_map<ll, int> m;

void pf(ll N, int add) { // pre-condition, N >= 1
  for (int i = 0; (i < (int) p.size()) && (p[i] * p[i] <= N); ++i) {
    while (N % p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      m[p[i]] += add;
    }
  }
  if (N != 1) m[N] += add;
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
  int n, k;
  sieve(100000);
  while (cin >> n >> k) {
    m.clear();
    k = min(k, n - k);
    for (int i = 2; i <= k; i++) pf(i, -1);
    for (int i = n - k + 1; i <= n; i++) pf(i, 1);
    ll ans = 1;
    for (auto& [pr, cnt] : m) {
      if (cnt) ans *= (cnt + 1);
    }
    cout << ans << '\n';
  }
}