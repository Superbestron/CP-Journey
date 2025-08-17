#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, a, b, n, m;

inline void solve() {
  cin >> a >> b >> n >> m;
  vi chips(n);
  map<int, set<ii>> rows, cols;
  for (int i = 0; i < n; i++) {
    int r, c; cin >> r >> c;
    r--; c--;
    rows[r].emplace(c, r);
    cols[c].emplace(r, c);
  }
  vi ans(2);
  int top_row = 0, btm_row = a - 1, left_col = 0, right_col = b - 1;
  for (int i = 0; i < m; i++) {
    char c; int k;
    cin >> c >> k;
    if (c == 'U') {
      auto it = rows.lower_bound(top_row);
      while (it != rows.end()) {
        if (it->first >= top_row + k) break;
        auto &[curr_row, st] = *it;
        auto set_it = st.lower_bound({left_col, 0});
        while (set_it != st.end()) {
          if (set_it->first > right_col) break;
          ans[i % 2]++;
          cols[set_it->first].erase({curr_row, set_it->first});
          set_it++;
        }
        it++;
      }
      top_row += k;
    } else if (c == 'D') {
      auto it = rows.upper_bound(btm_row);
      if (it == rows.begin()) continue;
      it--;
      while (true) {
        if (it->first <= btm_row - k) break;
        auto &[curr_row, st] = *it;
        auto set_it = st.lower_bound({left_col, 0});
        while (set_it != st.end()) {
          if (set_it->first > right_col) break;
          ans[i % 2]++;
          cols[set_it->first].erase({curr_row, set_it->first});
          set_it++;
        }
        if (it == rows.begin()) break;
        it--;
      }
      btm_row -= k;
    } else if (c == 'L') {
      auto it = cols.lower_bound(left_col);
      while (it != cols.end()) {
        if (it->first >= left_col + k) break;
        auto &[curr_col, st] = *it;
        auto set_it = st.lower_bound({top_row, 0});
        while (set_it != st.end()) {
          if (set_it->first > btm_row) break;
          ans[i % 2]++;
          rows[set_it->first].erase({curr_col, set_it->first});
          set_it++;
        }
        it++;
      }
      left_col += k;
    } else {
      auto it = cols.upper_bound(right_col);
      if (it == cols.begin()) continue;
      it--;
      while (true) {
        if (it->first <= right_col - k) break;
        auto &[curr_col, st] = *it;
        auto set_it = st.lower_bound({top_row, 0});
        while (set_it != st.end()) {
          if (set_it->first > btm_row) break;
          ans[i % 2]++;
          rows[set_it->first].erase({curr_col, set_it->first});
          set_it++;
        }
        if (it == cols.begin()) break;
        it--;
      }
      right_col -= k;
    }
  }
  cout << ans[0] << ' ' << ans[1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
