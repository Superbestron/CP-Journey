#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, x;

void solve() {
  cin >> n >> x;
  x++;
  vi a(n);
  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    int val; cin >> val;
    mp[i] = val;
  }
  int ans = -1;
  for (int i = 30; i >= 0; i--) {
    int cnt1 = 0;
    for (auto &[idx, num] : mp) {
      if (num & (1 << i)) cnt1++;
    }
    // if bit i 1
    if (cnt1 % 2 == 1) {
      if ((x & (1 << i)) == 0) {
        break;
      }
    } else {
      bool found = false;
      int sum;
      map<int, int> mp2 = mp;
      for (auto it = mp.begin(); it != mp.end();) {
        auto [idx, num] = *it;
        if (found) {
          if (num & (1 << i)) {
            sum ^= num;
            mp.erase(it);
            mp[idx] = sum;
            it = mp.find(idx);
            it++;
            found = false;
          } else {
            sum ^= num;
            it = mp.erase(it);
          }
        } else {
          if (num & (1 << i)) {
            found = true;
            sum = num;
            it = mp.erase(it);
          } else it++;
        }
      }
      if (x & (1 << i)) {
        ans = max(ans, (int) mp.size());
        mp = mp2;
      }
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
