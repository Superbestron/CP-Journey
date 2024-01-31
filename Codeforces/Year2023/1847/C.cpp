#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;
    unordered_set<int> has_pref;
    has_pref.insert(0);
    int cur_xor = 0;
    int ans = 0;
    for (auto i : a) {
      cur_xor ^= i;
      for (int pref : has_pref) ans = max(ans, pref ^ cur_xor);
      has_pref.insert(cur_xor);
    }
    cout << ans << '\n';
  }
}