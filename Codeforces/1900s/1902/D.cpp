#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, q;
string s;
unordered_map<char, ii> mp = {{'R', {1, 0}}, {'U', {0, 1}}, {'L', {-1, 0}}, {'D', {0, -1}}};

void solve() {
  cin >> n >> q >> s;
  map<ii, vi> st;
  vii idx_to_pos;
  int curr_x = 0, curr_y = 0;
  idx_to_pos.emplace_back(0, 0);
  for (int i = 0; i < n; i++) {
    auto &[x, y] = mp[s[i]];
    curr_x += x;
    curr_y += y;
    idx_to_pos.emplace_back(curr_x, curr_y);
    st[{curr_x, curr_y}].push_back(i + 1);
  }
  for (int i = 0; i < q; i++) {
    int x, y, l, r;
    cin >> x >> y >> l >> r;
    if (x == 0 && y == 0) {
      cout << "YES\n";
      continue;
    }
    // check if falls within the range [l, r - 1]
    // because this range might not contain valid coords anymore after the reverse of commands
    // possible to find outside range if true
    bool need_to_find_in_range = false;
    if (!st.count({x, y})) {
      // check inside range
      need_to_find_in_range = true;
    } else {
      auto &v = st[{x, y}];
      auto it = lower_bound(v.begin(), v.end(), l);
      auto it2 = upper_bound(v.begin(), v.end(), r - 1);
      if (it == v.begin() && it2 == v.end()) {
        // check inside range
        need_to_find_in_range = true;
      } else cout << "YES\n";
    }
    if (need_to_find_in_range) {
      // l - 1 and r remains the same coord
      auto [x_l, y_l] = idx_to_pos[l - 1];
      auto [x_r, y_r] = idx_to_pos[r];
      int flip_x = x_r + x_l - x, flip_y = y_r + y_l - y;
      // find flip_x and flip_y in [l, r]
      if (!st.count({flip_x, flip_y})) cout << "NO\n";
      else {
        auto &v = st[{flip_x, flip_y}];
        auto it = lower_bound(v.begin(), v.end(), l);
        if (it == v.end() || *it > r) cout << "NO\n";
        else cout << "YES\n";
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
