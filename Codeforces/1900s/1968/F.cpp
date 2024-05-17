#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, q, l, r;

inline void solve() {
  cin >> n >> q;
  vi a(n), pref(n + 1);
  for (int &i : a) cin >> i;
  map<int, vi> mp;
  mp[0].push_back(0);
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] ^ a[i];
    mp[pref[i + 1]].push_back(i + 1);
  }
  for (int i = 0; i < q; i++) {
    cin >> l >> r;
    int xor_sum = pref[r] ^ pref[l - 1];
    // partition into 2 segments
    if (xor_sum == 0) {
      cout << "YES\n";
      continue;
    }
    // partition into 3 segments
    int upper = *--lower_bound(mp[pref[l - 1]].begin(), mp[pref[l - 1]].end(), r);
    int lower = *lower_bound(mp[pref[r]].begin(), mp[pref[r]].end(), l);
    if (upper > lower) cout << "YES\n";
    else cout << "NO\n";
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
