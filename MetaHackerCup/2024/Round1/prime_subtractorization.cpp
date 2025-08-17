#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vll;

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000000);
  int T, N;
  cin >> T;
  ll ans = 1;
  map<ll, ll> mp;
  for (int i = 1; i < (int) p.size(); i++) {
    if (p[i] - p[i - 1] == 2) ans++;
    mp[p[i]] = ans;
  }
  for (int t = 1; t <= T; t++) {
    cin >> N;
    ll sol;
    if (N <= 4) {
      sol = 0;
    } else {
      sol = prev(mp.lower_bound(N + 1))->second;
    }
    printf("Case #%d: %lld\n", t, sol);
  }
}
