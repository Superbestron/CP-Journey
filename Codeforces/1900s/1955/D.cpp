#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, k;

void solve() {
  cin >> n >> m >> k;
  vi a(n), b(m);
  unordered_map<int, int> mp, b_mp;
  for (int &i : a) cin >> i;
  for (int &i : b) {
    cin >> i;
    b_mp[i]++;
  }
  int curr_k = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    int c = a[i];
    if (mp[c] + 1 <= b_mp[c]) curr_k++;
    mp[c]++;
    if (i >= m - 1 && curr_k >= k) ans++;
    // erase
    if (i >= m - 1) {
      int to_erase = a[i - m + 1];
      if (mp[to_erase] <= b_mp[to_erase]) curr_k--;
      mp[to_erase]--;
    }
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
