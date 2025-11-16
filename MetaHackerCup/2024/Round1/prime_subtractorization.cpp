#include <bits/stdc++.h>
#include "../../../Libraries/PrimalityCheck.cpp"
using namespace std;

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
