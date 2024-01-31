#include<bits/stdc++.h>
using namespace std;

int tc, n, q, val, t, s, i, v;

inline void solve() {
  cin >> n >> q;
  set<int> ones;
  int twosum = 0;
  for (int j = 0; j < n; j++) {
    cin >> val;
    if (val == 1) ones.insert(j);
  }
  while (q--) {
    cin >> t;
    if (t == 1) {
      cin >> s;
      int ones_cnt = ones.size();
      if ((s - ones_cnt) % 2 == 0) {
        if (s <= 2 * n - ones_cnt) cout << "YES\n";
        else cout << "NO\n";
      }
      else {
        if (ones_cnt == 0) cout << "NO\n";
        else {
          auto l = ones.begin();
          auto r = ones.rbegin();
          int first_one_idx = *l, last_one_idx = *r;
          if (s <= max(2 * last_one_idx - (ones_cnt - 1), 2 * (n - first_one_idx - 1) - (ones_cnt - 1))) {
            cout << "YES\n";
          } else cout << "NO\n";
        }
      }
     } else {
      cin >> i >> v;
      i--;
      ones.erase(i);
      if (v == 1) ones.insert(i);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> tc;
  while (tc--) {
    solve();
  }
}
