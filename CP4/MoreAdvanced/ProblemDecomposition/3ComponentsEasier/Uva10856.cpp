#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes
int MAX_N = 2703666;
vector<ll> memo(MAX_N, -1);

// Take note for this question the sample output for "Not possible." is missing a full stop.

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

ll numPF(ll N) {
  ll &ans = memo[N];
  if (ans != -1) return ans;
  ans = 0;
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0) {
      return ans = 1 + numPF(N /= p[i]);
    }
  return ans = bs[N];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000005);
  int x, tc = 1;
  for (int i = MAX_N - 1; i >= 0; i--) {
    numPF(i);
  }
  for (int i = 1; i < MAX_N; i++) {
    memo[i] += memo[i - 1];
  }
  int ans = 0;
  while (cin >> x) {
    bool found = false;
    if (x < 0) break;
    if (x == 0) {
      cout << "Case " << tc++ << ": 0!\n";
      continue;
    }
    int l = 0, r = MAX_N - 1;
    while (l <= r) {
      int m = l + (r - l) / 2;
      if (memo[m] == x) {
        found = true;
        ans = m;
        break;
      }
      if (memo[m] < x) l = m + 1;
      else r = m - 1;
    }

    if (found) cout << "Case " << tc++ << ": "  << ans << "!\n";
    else cout << "Case " << tc++ << ": Not possible.\n";
  }
}
