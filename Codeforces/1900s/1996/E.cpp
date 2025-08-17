#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
const ll MOD = 1e9 + 7;
string s;

inline void solve() {
  cin >> s;
  n = s.size();
  vi pref0(s.size() + 1), pref1(s.size() + 1), pref(s.size() + 1);
  unordered_map<int, ll> mp;
  mp[0]++;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : -1);
    ans = (ans + mp[pref[i + 1]] * (n - i)) % MOD;
    mp[pref[i + 1]] += (i + 2);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
